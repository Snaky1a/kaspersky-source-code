!ifdef KAV
!define PRODUCT_FULLNAME_NOM "Kaspersky Anti-Virus ${VER_NAME}"
!define PRODUCT_FULLNAME_GEN "Kaspersky Anti-Virus ${VER_NAME}"

!define PRODUCT_SHRTNAME_NOM "${PRODUCT_FULLNAME_NOM}"
!define PRODUCT_SHRTNAME_GEN "${PRODUCT_FULLNAME_GEN}"

!else ifdef KIS
!define PRODUCT_FULLNAME_NOM "Kaspersky Internet Security ${VER_NAME}"
!define PRODUCT_FULLNAME_GEN "${PRODUCT_FULLNAME_NOM}"

!define PRODUCT_SHRTNAME_NOM "${PRODUCT_FULLNAME_NOM}"
!define PRODUCT_SHRTNAME_GEN "${PRODUCT_FULLNAME_GEN}"

!else ifdef WKS
!define PRODUCT_FULLNAME_NOM "Kaspersrky Anti-Virus ${VER_NAME} for Windows Workstations"
!define PRODUCT_FULLNAME_GEN "Kaspersky Anti-Virus ${VER_NAME} for Windows Workstations"

!define PRODUCT_SHRTNAME_NOM "Kaspersky Anti-Virus ${VER_NAME}"
!define PRODUCT_SHRTNAME_GEN "Kaspersky Anti-Virus ${VER_NAME}"

!else ifdef SRV
!define PRODUCT_FULLNAME_NOM "Kaspersky Anti-Virus ${VER_NAME} for Windows Servers"
!define PRODUCT_FULLNAME_GEN "Kaspersksy Anti-Virus ${VER_NAME} for Windows Servers"

!define PRODUCT_SHRTNAME_NOM "Kaspersky Anti-Virus ${VER_NAME}"
!define PRODUCT_SHRTNAME_GEN "Kaspersky Anti-Virus ${VER_NAME}"

!else ifdef SOS
!define PRODUCT_FULLNAME_NOM "Kaspersky Anti-Virus ${VER_NAME} SOS"
!define PRODUCT_FULLNAME_GEN "Kaspersky Anti-Virus ${VER_NAME} SOS"

!define PRODUCT_SHRTNAME_NOM "Kaspersky Anti-Virus ${VER_NAME}"
!define PRODUCT_SHRTNAME_GEN "Kaspersky Anti-Virus ${VER_NAME}"
!endif

LangString TEXT_PRODUCT_NAME  ${LANG_FRENCH} "${PRODUCT_SHRTNAME_NOM}"

LangString TEXT_SETUP_CAPTION ${LANG_FRENCH} "Programme d'installation de ${PRODUCT_SHRTNAME_GEN}"

LangString TEXT_WELCOMEPAGE_TITLE         ${LANG_FRENCH} "Bienvenue dans le programme d'extraction du fichier d'installation de ${PRODUCT_SHRTNAME_GEN}"
LangString TEXT_WELCOMEPAGE_TEXT          ${LANG_FRENCH} "Ce programme va extraire le fichier d'installation de ${PRODUCT_FULLNAME_GEN} sur votre ordinateur.\r\n\r\nCliquez sur 'Suivant' pour continuer."

LangString MUI_TEXT_DIRECTORY_TITLE       ${LANG_FRENCH} "S�lection du r�pertoire d'installation"
LangString MUI_TEXT_DIRECTORY_SUBTITLE    ${LANG_FRENCH} "S�lectionnez le r�pertoire d'installation"

LangString TEXT_DIRECTORYPAGE_TOP         ${LANG_FRENCH} "Le programme va extraire le fichier d'installation de ${PRODUCT_FULLNAME_GEN} dans le r�pertoire s�lectionn�. Pour extraire le fichier dans un autre r�pertoire, cliquez sur  'Parcourir' et indiquez le nouveau r�pertoire. Clliquez sur 'Installer' pour lancer l'extraction."
LangString TEXT_DIRECTORYPAGE_DESTINATION ${LANG_FRENCH} "R�pertoire pour le fichier d'installation"

LangString ^DirBrowseText ${LANG_FRENCH} "Pr�cisez le r�pertoire pour l'extraction de ${PRODUCT_SHRTNAME_GEN}"

LangString MUI_TEXT_INSTALLING_TITLE      ${LANG_FRENCH} "Copie des fichiers"
LangString MUI_TEXT_INSTALLING_SUBTITLE   ${LANG_FRENCH} "La copie des fichiers d'installation de ${PRODUCT_FULLNAME_GEN} est en cours. Veuillez patienter..."

LangString TEXT_FINISHPAGE_TITLE          ${LANG_FRENCH} "L'extraction du fichier d'installation de ${PRODUCT_SHRTNAME_GEN} est termin�e"
LangString TEXT_FINISHPAGE_TEXT           ${LANG_FRENCH} "L'extraction du fichier d'installation de ${PRODUCT_FULLNAME_GEN} est termin�e.\r\n\r\nCliquez sur $\"Terminer$\" pour quitter le programme."
LangString TEXT_FINISHPAGE_RUN            ${LANG_FRENCH} "Lancer l'installation de ${PRODUCT_SHRTNAME_GEN}"

;Version info
VIProductVersion "${VER_FULL}"
VIAddVersionKey /LANG=${LANG_FRENCH} "FileDescription" "Programme d'installation de ${PRODUCT_FULLNAME_GEN}"
VIAddVersionKey /LANG=${LANG_FRENCH} "CompanyName" "Kaspersky Lab"
VIAddVersionKey /LANG=${LANG_FRENCH} "FileVersion" "${VER_FULL}"
VIAddVersionKey /LANG=${LANG_FRENCH} "LegalTrademarks" "Kaspersky� Anti-Virus est une marque d�pos�e de Kaspersky Lab."
VIAddVersionKey /LANG=${LANG_FRENCH} "LegalCopyright" 'Kaspersky Lab Ltd. 1996-2007. Tous droits r�serv�s.'
VIAddVersionKey /LANG=${LANG_FRENCH} "ProductName" "${PRODUCT_FULLNAME_NOM}"
VIAddVersionKey /LANG=${LANG_FRENCH} "ProductVersion" "${VER_FULL}"
