include(FeatureSummary)

find_program(LLVMAR_EXECUTABLE
        NAMES llvm-ar llvm-ar-10 llvm-ar-11 llvm-ar-*
        DOC "The llvm-ar executable"
        )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LLVMAr
        DEFAULT_MSG
        LLVMAR_EXECUTABLE)

SET_PACKAGE_PROPERTIES(LLVMAr PROPERTIES
        URL https://llvm.org/docs/CommandGuide/llvm-ar.html
        DESCRIPTION "create, modify, and extract from archives"
        )