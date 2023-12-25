!ifdef KAV
!define PRODUCT_FULLNAME_NOM "��������� ����������� ${VER_NAME}"
!define PRODUCT_FULLNAME_GEN "���������� ����������� ${VER_NAME}"

!define PRODUCT_SHRTNAME_NOM "${PRODUCT_FULLNAME_NOM}"
!define PRODUCT_SHRTNAME_GEN "${PRODUCT_FULLNAME_GEN}"

!else ifdef KIS
!define PRODUCT_FULLNAME_NOM "Kaspersky Internet Security ${VER_NAME}"
!define PRODUCT_FULLNAME_GEN "${PRODUCT_FULLNAME_NOM}"

!define PRODUCT_SHRTNAME_NOM "${PRODUCT_FULLNAME_NOM}"
!define PRODUCT_SHRTNAME_GEN "${PRODUCT_FULLNAME_GEN}"

!else ifdef WKS
!define PRODUCT_FULLNAME_NOM "��������� ����������� ${VER_NAME} ��� Windows Workstations"
!define PRODUCT_FULLNAME_GEN "���������� ����������� ${VER_NAME} ��� Windows Workstations"

!define PRODUCT_SHRTNAME_NOM "��������� ����������� ${VER_NAME}"
!define PRODUCT_SHRTNAME_GEN "���������� ����������� ${VER_NAME}"

!else ifdef SRV
!define PRODUCT_FULLNAME_NOM "��������� ����������� ${VER_NAME} ��� Windows Servers"
!define PRODUCT_FULLNAME_GEN "���������� ����������� ${VER_NAME} ��� Windows Servers"

!define PRODUCT_SHRTNAME_NOM "��������� ����������� ${VER_NAME}"
!define PRODUCT_SHRTNAME_GEN "���������� ����������� ${VER_NAME}"

!else ifdef SOS
!define PRODUCT_FULLNAME_NOM "��������� ����������� ${VER_NAME} SOS"
!define PRODUCT_FULLNAME_GEN "���������� ����������� ${VER_NAME} SOS"

!define PRODUCT_SHRTNAME_NOM "��������� ����������� ${VER_NAME}"
!define PRODUCT_SHRTNAME_GEN "���������� ����������� ${VER_NAME}"
!endif

LangString TEXT_PRODUCT_NAME  ${LANG_RUSSIAN} "${PRODUCT_SHRTNAME_NOM}"

LangString TEXT_SETUP_CAPTION ${LANG_RUSSIAN} "��������� ��������� ${PRODUCT_SHRTNAME_GEN}"

LangString TEXT_WELCOMEPAGE_TITLE         ${LANG_RUSSIAN} "��� ������������ ��������� ���������� ������������ ${PRODUCT_SHRTNAME_GEN}"
LangString TEXT_WELCOMEPAGE_TEXT          ${LANG_RUSSIAN} "��� ��������� ��������� ����������� ${PRODUCT_FULLNAME_GEN} �� ��� ���������.\r\n\r\n������� ������ '�����' ��� �����������."

LangString MUI_TEXT_DIRECTORY_TITLE       ${LANG_RUSSIAN} "����� ����� ���������"
LangString MUI_TEXT_DIRECTORY_SUBTITLE    ${LANG_RUSSIAN} "�������� ����� ��� ���������"

LangString TEXT_DIRECTORYPAGE_TOP         ${LANG_RUSSIAN} "��������� ��������� ����������� ${PRODUCT_FULLNAME_GEN} � ��������� �����. ����� ����������� ����������� � ������ �����, ������� ������ '�����' � ������� ��. ������� ������ '����������', ����� ������ ����������."
LangString TEXT_DIRECTORYPAGE_DESTINATION ${LANG_RUSSIAN} "����� ��� ������������"

LangString ^DirBrowseText ${LANG_RUSSIAN} "������� ����� ��� ���������� ${PRODUCT_SHRTNAME_GEN}"

LangString MUI_TEXT_INSTALLING_TITLE      ${LANG_RUSSIAN} "����������� ������"
LangString MUI_TEXT_INSTALLING_SUBTITLE   ${LANG_RUSSIAN} "���������, ���� ����������� ������ ������������ ${PRODUCT_FULLNAME_GEN}..."

LangString TEXT_FINISHPAGE_TITLE          ${LANG_RUSSIAN} "���������� ������������ ${PRODUCT_SHRTNAME_GEN} ���������"
LangString TEXT_FINISHPAGE_TEXT           ${LANG_RUSSIAN} "���������� ������������ ${PRODUCT_FULLNAME_GEN} ���������.\r\n\r\n������� ������ $\"������$\" ��� ������ �� ���������."
LangString TEXT_FINISHPAGE_RUN            ${LANG_RUSSIAN} "��������� ��������� ${PRODUCT_SHRTNAME_GEN}"

;Version info
VIProductVersion "${VER_FULL}"
VIAddVersionKey /LANG=${LANG_RUSSIAN} "FileDescription" "��������� ��������� ${PRODUCT_FULLNAME_GEN}"
VIAddVersionKey /LANG=${LANG_RUSSIAN} "CompanyName" "����������� �����������"
VIAddVersionKey /LANG=${LANG_RUSSIAN} "FileVersion" "${VER_FULL}"
VIAddVersionKey /LANG=${LANG_RUSSIAN} "LegalTrademarks" "��������� ����������� - ������������������ �������� ����� ����������� �����������."
VIAddVersionKey /LANG=${LANG_RUSSIAN} "LegalCopyright" '��� "����������� �����������", 1996-2007. ��� ����� ��������.'
VIAddVersionKey /LANG=${LANG_RUSSIAN} "ProductName" "${PRODUCT_FULLNAME_NOM}"
VIAddVersionKey /LANG=${LANG_RUSSIAN} "ProductVersion" "${VER_FULL}"
