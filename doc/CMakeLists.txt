include(UseLATEX)

set(DOCUMENT_1 TKOM-Wstepna-Stawczyk-Przemyslaw)

add_latex_document(${DOCUMENT_1}.tex FORCE_PDF TARGET_NAME ${DOC})

latex_get_output_path(LATEX_OUT)
add_custom_command(TARGET ${DOC} POST_BUILD COMMAND cp ${LATEX_OUT}/${DOCUMENT_1}.pdf ${PROJECT_SOURCE_DIR}/doc/)
