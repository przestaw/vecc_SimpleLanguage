function(doxygen LaTeX)
    set(DOXYGEN_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/doc/doxygen)

    set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
    set(DOXYGEN_PROJECT_BRIEF ${PROJECT_DESCRIPTION})

    set(DOXYGEN_HTML_COLORSTYLE_HUE 123)
    set(DOXYGEN_HTML_COLORSTYLE_SAT 69)
    set(DOXYGEN_HTML_COLORSTYLE_GAMMA 240)

    set(DOXYGEN_HTML_DYNAMIC_MENUS YES)
    set(DOXYGEN_HTML_DYNAMIC_SECTIONS YES)

    set(DOXYGEN_FILE_PATTERNS *.h *.c *.cpp *.hpp *.cc *.cxx *.hxx *.hh)
    set(DOXYGEN_EXTRACT_ALL YES)

    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_MARKDOWN_SUPPORT YES)

    set(DOXYGEN_GENERATE_LATEX NO)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)

    doxygen_add_docs(${DOC}-doxygen ${LIB_INC} ${LIB_SRC})
endfunction()

if (LATEX_FOUND)
    include(UseLATEX)

    latex_get_output_path(LATEX_OUT)

    set(DOCUMENT_1 TKOM-Stawczyk-Przemyslaw)

    add_latex_document(${DOCUMENT_1}.tex TARGET_NAME ${DOC}-latex)
    add_custom_command(TARGET ${DOC}-latex POST_BUILD COMMAND cp ${LATEX_OUT}/${DOCUMENT_1}.pdf ${PROJECT_SOURCE_DIR}/doc/)

    if(DOXYGEN_FOUND)
        DOXYGEN(NO)
        add_custom_target(${DOC} command echo "Documentation : html, polish pdf")
        add_dependencies(${DOC} ${DOC}-latex ${DOC}-doxygen)
    else()
        add_custom_target(${DOC} command echo "Documentation : polish pdf")
        add_dependencies(${DOC} ${DOC}-latex)
    endif()
elseif(DOXYGEN_FOUND)
    DOXYGEN(NO)

    add_custom_target(${DOC} command echo "Documentation : html")
    add_dependencies(${DOC} ${DOC}-doxygen)
endif()


