//
// Created by przemek on 19.03.2020.
//

#include <AST/expression/additive_expr.h>
#include <AST/expression/and_logic_expr.h>
#include <AST/expression/base_logic_expr.h>
#include <AST/expression/base_math_expr.h>
#include <AST/expression/multiply_expr.h>
#include <AST/expression/or_logic_expr.h>
#include <AST/expression/realtion_expr.h>
#include <AST/statement/assign_stmt.h>
#include <AST/statement/function_call.h>
#include <AST/statement/if_stmt.h>
#include <AST/statement/print_stmt.h>
#include <AST/statement/return_stmt.h>
#include <AST/statement/while_stmt.h>
#include <parser/parser.h>
#include <utility>

using namespace vecc;
using namespace vecc::ast;

Parser::Parser(const LogLevel &logLevel, std::ostream &out)
    : logLevel_(logLevel), out_(out),
      scanner_(std::unique_ptr<Scanner>(nullptr)),
      currentProgram(std::make_unique<Program>()), currentContext(nullptr) {
}

Parser::Parser(std::unique_ptr<Reader> source, const LogLevel &logLevel,
               std::ostream &out)
    : logLevel_(logLevel), out_(out),
      scanner_(std::make_unique<Scanner>(std::move(source), logLevel, out)),
      currentProgram(std::make_unique<Program>()), currentContext(nullptr) {
}

void Parser::setSource(std::unique_ptr<Reader> source) {
  scanner_ =
      std::make_unique<Scanner>(Scanner(std::move(source), logLevel_, out_));
}

void Parser::parse() {
  if (scanner_) {
    scanner_->readToken();
    while (scanner_->getToken().getType() != Token::Type::EoF) {
      expectNextToken(Token::Type::Function);
      scanner_->readToken();
      parseFunctionDef();
    }
  } else {
    throw error::NoInputStream();
  }
}

std::unique_ptr<Program> Parser::getProgram() {
  std::unique_ptr<Program> temp = std::make_unique<Program>();
  std::swap(currentProgram, temp);
  currentContext = nullptr;
  return temp;
}

void Parser::parseFunctionDef() {
  expectNextToken(Token::Type::Identifier);
  Token funToken = scanner_->getToken();
  scanner_->readToken();

  if (!currentProgram->existFunction(funToken.getLiteral())) {
    std::unique_ptr<Function> function =
        std::make_unique<Function>(funToken.getLiteral());

    expectNextToken(Token::Type::ParenthesisOpen);
    scanner_->readToken();
    parseParameters(*function);

    expectNextToken(Token::Type::CurlyBracketOpen);
    scanner_->readToken();

    // NOTE : need to add to allow recursion, reference to save
    Function *funRef = function.get();
    currentProgram->addFunction(std::move(function));

    parseStatementBlock(funRef->getFunctionBody());

    if (logLevel_ >= LogLevel::CreatedFunctions) {
      out_ << FCYN(BOLD("Function Log : \n")) "Function : " FCYN(
          "" + funToken.getLiteral() + "") " has been created \n";
    }
  } else {
    throw error::RedefinedFun(funToken);
  }
}

void Parser::parseParameters(Function &def) {
  if (scanner_->getToken().getType() == Token::Type::Identifier) {
    def.addParameter(scanner_->getToken().getLiteral());
    scanner_->readToken();

    while (scanner_->getToken().getType() == Token::Type::Comma) {
      scanner_->readToken();
      expectNextToken(Token::Type::Identifier);
      def.addParameter(scanner_->getToken().getLiteral());
      scanner_->readToken();
    }
  }
  expectNextToken(Token::Type::ParenthesisClose);
  scanner_->readToken();
}

void Parser::parseStatementBlock(StatementBlock &newBlock) {
  currentContext = &newBlock.getContext();

  while (scanner_->getToken().getType() != Token::Type::CurlyBracketClose) {
    Token token = scanner_->readToken();
    switch (token.getType()) {
    default:
      throw error::UnexpectedToken(
          token, {Token::Type::If, Token::Type::While, Token::Type::Return,
                  Token::Type::Var, Token::Type::Identifier, Token::Type::Print,
                  Token::Type::CurlyBracketOpen});
      // no need to break
    case Token::Type::Var:
      newBlock.addInstruction(parseInitStatement());
      break;
    case Token::Type::Identifier:
      // funCallStmt or assignment
      newBlock.addInstruction(parseIdentifier());
      break;
    case Token::Type::If:
      newBlock.addInstruction(parseIfStatement());
      break;
    case Token::Type::While:
      newBlock.addInstruction(parseWhileStatement());
      break;
    case Token::Type::Return:
      newBlock.addInstruction(parseReturnStatement());
      break;
    case Token::Type::Print:
      newBlock.addInstruction(parsePrintStatement());
      break;
    case Token::Type::CurlyBracketOpen:
      auto internalBlock = std::make_unique<StatementBlock>(currentContext);
      scanner_->readToken(); // move to next token
      parseStatementBlock(*internalBlock);
      newBlock.addInstruction(std::move(internalBlock));
    }
  }
  // Note: we now exit this block
  currentContext = currentContext->getParentContext();
}

Variable Parser::parseVectorValue() {
  std::vector<int> variables;

  auto parseValue = [&]() {
    bool minus = tryConsumeToken(Token::Type::Minus);
    expectNextToken(Token::Type::NumberString);
    if (minus) {
      variables.push_back(-scanner_->getToken().getNumberValue());
    } else {
      variables.push_back(scanner_->getToken().getNumberValue());
    }
  };

  scanner_->readToken(); // parse token after vec
  expectNextToken(Token::Type::ParenthesisOpen);
  scanner_->readToken();
  parseValue();
  expectNextToken(Token::Type::Comma);
  scanner_->readToken();
  parseValue();
  // check if 3 dimensional vector
  // FIXME : could be any dim vector -> while
  if (tryConsumeToken(Token::Type::Comma)) {
    parseValue();
  }
  expectNextToken(Token::Type::ParenthesisClose);
  scanner_->readToken();

  return Variable(std::move(variables));
}

std::unique_ptr<Statement>
Parser::parseAssignStatement(const std::shared_ptr<Variable> &variable) {
  Position position;
  auto rValueParse = [&]() {
    expectNextToken(Token::Type::Assignment);
    position = scanner_->getToken().getTokenPos();
    scanner_->readToken();
    std::unique_ptr<Expression> logicExpr(parseOrExpression());
    expectNextToken(Token::Type::Semicolon);
    scanner_->readToken();
    return logicExpr;
  };

  std::unique_ptr<AssignStatement> assignStmt;
  if (tryConsumeToken(Token::Type::BracketOpen)) {
    // indexed access identifier[position]
    expectNextToken(Token::Type::NumberString);
    const auto val = scanner_->getToken().getNumberValue();
    scanner_->readToken();
    expectNextToken(Token::Type::BracketClose);
    scanner_->readToken();
    assignStmt =
        std::make_unique<AssignStatement>(*(variable), val, rValueParse());
  } else {
    // whole var/vec accesss
    assignStmt = std::make_unique<AssignStatement>(*(variable), rValueParse());
  }
  assignStmt->setPosition(position);
  return assignStmt;
}

std::unique_ptr<Statement> Parser::parseInitStatement() {
  scanner_->readToken();
  expectNextToken(Token::Type::Identifier);
  Token identifier  = scanner_->getToken();
  Position position = identifier.getTokenPos();
  scanner_->readToken();

  if (!currentContext->existVariable(identifier.getLiteral())) {
    std::unique_ptr<AssignStatement> assignStmt;
    currentContext->addVariable(identifier.getLiteral(), Variable());

    if (scanner_->getToken().getType() == Token::Type::Assignment) {
      position = scanner_->getToken().getTokenPos();
      scanner_->readToken();
      assignStmt = std::make_unique<AssignStatement>(
          *currentContext->findVariable(identifier.getLiteral(), identifier),
          parseOrExpression());
      assignStmt->setPosition(position); // = pos
    } else {
      assignStmt = std::make_unique<AssignStatement>(
          *currentContext->findVariable(identifier.getLiteral(), identifier),
          std::make_unique<BaseMathExpr>(std::make_unique<Variable>()));
      assignStmt->setPosition(position); // id pos
    }

    expectNextToken(Token::Type::Semicolon);
    scanner_->readToken();
    return assignStmt;

  } else {
    throw error::RedefinedVar(identifier);
  }
}

std::unique_ptr<Statement> Parser::parseIdentifier() {
  std::unique_ptr<Statement> stmt;
  Token identifier = scanner_->getToken();
  scanner_->readToken();

  if (scanner_->getToken().getType() == Token::Type::ParenthesisOpen) {
    // function
    scanner_->readToken();
    stmt = parseFunctionCall(identifier);
    expectNextToken(Token::Type::Semicolon);
    scanner_->readToken();
  } else {
    // variable
    stmt = parseAssignStatement(
        // findVariable checks if Variable exists
        currentContext->findVariable(identifier.getLiteral(), identifier));
  }

  return stmt;
}

std::unique_ptr<Statement> Parser::parseFunctionCall(const Token &function) {
  if (!currentProgram->existFunction(function.getLiteral())) {
    throw error::UndefinedFun(function);
  }

  Function &fun = currentProgram->findFunction(function.getLiteral());

  std::unique_ptr<FunctionCallStatement> funCall =
      std::make_unique<FunctionCallStatement>(fun);

  if (scanner_->getToken().getType() != Token::Type::ParenthesisClose) {
    do {
      funCall->addArgument(parseOrExpression());
    } while (tryConsumeToken(Token::Type::Comma));
    expectNextToken(Token::Type::ParenthesisClose);
  }
  scanner_->readToken(); // read ParenthesisClose

  if (fun.size() == funCall->size()) {
    return funCall;
  } else {
    throw error::MismatchedArgumentsCount(function, fun.size(),
                                          funCall->size());
  }
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
  scanner_->readToken(); // read If
  expectNextToken(Token::Type::ParenthesisOpen);
  scanner_->readToken();

  std::unique_ptr<Expression> condition = parseOrExpression();

  expectNextToken(Token::Type::ParenthesisClose);
  scanner_->readToken();

  std::unique_ptr<IfStatement> ifStmt =
      std::make_unique<IfStatement>(std::move(condition));

  expectNextToken(Token::Type::CurlyBracketOpen);
  scanner_->readToken();
  // connect to context
  ifStmt->trueBlock().getContext().setParentContext(currentContext);
  parseStatementBlock(ifStmt->trueBlock());

  if (scanner_->getToken().getType() == Token::Type::Else) {
    scanner_->readToken();
    expectNextToken(Token::Type::CurlyBracketOpen);
    scanner_->readToken();
    // connect to context
    ifStmt->falseBlock().getContext().setParentContext(currentContext);
    parseStatementBlock(ifStmt->falseBlock());
  }

  return ifStmt;
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
  scanner_->readToken(); // read While
  expectNextToken(Token::Type::ParenthesisOpen);
  scanner_->readToken();

  std::unique_ptr<Expression> condition = parseOrExpression();

  expectNextToken(Token::Type::ParenthesisClose);
  scanner_->readToken();

  std::unique_ptr<WhileStatement> whileStmt =
      std::make_unique<WhileStatement>(std::move(condition));

  expectNextToken(Token::Type::CurlyBracketOpen);
  scanner_->readToken();
  // connect to context
  whileStmt->getWhileBody().getContext().setParentContext(currentContext);
  parseStatementBlock(whileStmt->getWhileBody());

  return whileStmt;
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
  scanner_->readToken(); // read Return
  std::unique_ptr<ReturnStatement> returnStmt =
      std::make_unique<ReturnStatement>(parseOrExpression());
  expectNextToken(Token::Type::Semicolon);
  scanner_->readToken();
  return returnStmt;
}

std::unique_ptr<Statement> Parser::parsePrintStatement() {
  scanner_->readToken(); // read Print
  expectNextToken(Token::Type::ParenthesisOpen);
  scanner_->readToken();

  std::unique_ptr<PrintStatement> printStmt =
      std::make_unique<PrintStatement>(out_);
  do {
    if (scanner_->getToken().getType() == Token::Type::CharacterString) {
      printStmt->addString(scanner_->getToken().getLiteral());
      scanner_->readToken();
    } else {
      printStmt->addExpression(parseOrExpression());
    }
  } while (tryConsumeToken(Token::Type::Comma));

  expectNextToken(Token::Type::ParenthesisClose);
  scanner_->readToken();
  expectNextToken(Token::Type::Semicolon);
  scanner_->readToken();

  return printStmt;
}

std::unique_ptr<Expression> Parser::parseOrExpression() {
  std::unique_ptr<OrLogicExpr> orExpr =
      std::make_unique<OrLogicExpr>(parseAndExpression());

  while (scanner_->getToken().getType() == Token::Type::Or) {
    // add operands until other token will appear
    scanner_->readToken();
    orExpr->addOperand(parseAndExpression());
  }

  return orExpr;
}

std::unique_ptr<Expression> Parser::parseAndExpression() {
  std::unique_ptr<AndLogicExpr> andExpr =
      std::make_unique<AndLogicExpr>(parseRelationalExpression());

  while (scanner_->getToken().getType() == Token::Type::And) {
    // add operands until other token will appear
    scanner_->readToken();
    andExpr->addOperand(parseRelationalExpression());
  }

  return andExpr;
}

std::unique_ptr<Expression> Parser::parseRelationalExpression() {
  std::unique_ptr<Expression> lValue = parseBaseLogicExpression();

  Token token = scanner_->getToken();

  auto makeRel = [&](const RelationExpr::OperatorType &operatorType) {
    scanner_->readToken();
    // make expr using token pos
    return std::make_unique<RelationExpr>(std::move(lValue), operatorType,
                                          parseBaseLogicExpression(),
                                          token.getTokenPos());
  };

  switch (token.getType()) {
  case Token::Type::Equality:
    return makeRel(RelationExpr::OperatorType::Equal);

  case Token::Type::Inequality:
    return makeRel(RelationExpr::OperatorType::NotEqual);

  case Token::Type::Less:
    return makeRel(RelationExpr::OperatorType::Less);

  case Token::Type::Greater:
    return makeRel(RelationExpr::OperatorType::Greater);

  case Token::Type::LessOrEqual:
    return makeRel(RelationExpr::OperatorType::LessOrEqual);

  case Token::Type::GreaterOrEqual:
    return makeRel(RelationExpr::OperatorType::GreaterOrEqual);

  default:
    // Not an Relation => just PassValue
    return lValue;
  }
}

std::unique_ptr<Expression> Parser::parseBaseLogicExpression() {
  // return negated if Token: Negation occured
  bool negated = tryConsumeToken(Token::Type::Negation);
  return std::make_unique<BaseLogicExpr>(parseAdditiveExpression(), negated);
}

std::unique_ptr<Expression> Parser::parseAdditiveExpression() {
  std::unique_ptr<AdditiveExpr> addExpr =
      std::make_unique<AdditiveExpr>(parseMultiplyExpression());

  Token token;

  auto addOp = [&](const AdditiveExpr::OperatorType &operatorType) {
    scanner_->readToken();
    addExpr->addOperand(parseMultiplyExpression(), operatorType,
                        token.getTokenPos());
  };

  // NOTE : "infinite" loop allows for easy and more readable handling multiple
  // cases
  for (;;) {
    token = scanner_->getToken();
    switch (token.getType()) {
    case Token::Type::Plus:
      addOp(AdditiveExpr::OperatorType::Add);
      break;
    case Token::Type::Minus:
      addOp(AdditiveExpr::OperatorType::Substract);
      break;
    default:
      // NOTE : when no more operands - return
      return addExpr;
    }
  }
}

std::unique_ptr<Expression> Parser::parseMultiplyExpression() {
  std::unique_ptr<MultiplyExpr> multiExpr =
      std::make_unique<MultiplyExpr>(parseBaseMathExpression());

  Token token;

  auto addOp = [&](const MultiplyExpr::OperatorType &operatorType) {
    scanner_->readToken();
    multiExpr->addOperand(parseBaseMathExpression(), operatorType,
                          token.getTokenPos());
  };

  // NOTE : "infinite" loop allows for easy and more readable handling multiple
  // cases
  for (;;) {
    token = scanner_->getToken();
    switch (token.getType()) {
    case Token::Type::Divide:
      addOp(MultiplyExpr::OperatorType::Divide);
      break;
    case Token::Type::Modulo:
      addOp(MultiplyExpr::OperatorType::Modulo);
      break;
    case Token::Type::Multiply:
      addOp(MultiplyExpr::OperatorType::Multiply);
      break;
    default:
      // NOTE : when no more operands - return
      return multiExpr;
    }
  }
}

std::unique_ptr<Expression> Parser::parseBaseMathExpression() {
  bool unaryMathOp = tryConsumeToken(Token::Type::Minus);

  Token token = scanner_->getToken();
  switch (token.getType()) {
  case Token::Type::NumberString:
    scanner_->readToken();
    return std::make_unique<BaseMathExpr>(Variable({token.getNumberValue()}),
                                          unaryMathOp);

  case Token::Type::Vec:
    return std::make_unique<BaseMathExpr>(parseVectorValue(), unaryMathOp);

  case Token::Type::Identifier:
    return parseIdentifierValue(unaryMathOp);

  case Token::Type::ParenthesisOpen:
    return parseParentExpression(unaryMathOp);

  default:
    throw error::UnexpectedToken(scanner_->getToken(),
                                 {Token::Type::NumberString, Token::Type::Vec,
                                  Token::Type::Identifier,
                                  Token::Type::ParenthesisOpen});
  }
}

std::unique_ptr<Expression>
Parser::parseParentExpression(const bool &unaryMathOp) {
  scanner_->readToken();
  std::unique_ptr<BaseMathExpr> ret =
      std::make_unique<BaseMathExpr>(parseOrExpression(), unaryMathOp);
  expectNextToken(Token::Type::ParenthesisClose);
  scanner_->readToken();
  return ret;
}

std::unique_ptr<Expression>
Parser::parseIdentifierValue(const bool &unaryMathOp) {
  Token identifier = scanner_->getToken();
  scanner_->readToken();
  if (tryConsumeToken(Token::Type::ParenthesisOpen)) {
    // funCall
    return std::make_unique<BaseMathExpr>(parseFunctionCall(identifier),
                                          unaryMathOp);
  } else {
    // variable
    // NOTE : checking of variable existance is done in findVariable
    if (tryConsumeToken(Token::Type::BracketOpen)) {
      expectNextToken(Token::Type::NumberString);
      const auto val = scanner_->getToken().getNumberValue();
      scanner_->readToken();
      expectNextToken(Token::Type::BracketClose);
      scanner_->readToken();

      return std::make_unique<BaseMathExpr>(
          currentContext->findVariable(identifier.getLiteral(), identifier),
          val, unaryMathOp);
    } else {
      return std::make_unique<BaseMathExpr>(
          currentContext->findVariable(identifier.getLiteral(), identifier),
          unaryMathOp);
    }
  }
}
