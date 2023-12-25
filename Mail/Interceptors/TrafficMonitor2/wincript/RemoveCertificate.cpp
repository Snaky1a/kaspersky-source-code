#include "winverifytrust.h"

bool RemoveCertificate(char* szFileName, HCERTSTORE hCollectionStore)
{
	bool bResult = false;

	//--------------------------------------------------------------------
	// Declare and initialize variables.
	
	HCERTSTORE      hSystemStoreCA = NULL;
	HCERTSTORE      hSystemStoreMY = NULL;
	HCERTSTORE      hSystemStoreROOT = NULL;
	PCCERT_CONTEXT  pStoredCert = NULL;
	PCCERT_CONTEXT  pTargetCert = NULL;
	HCERTSTORE      hFileStore = NULL;
	DWORD			dwVerificationFlags = 
		CERT_STORE_SIGNATURE_FLAG | 
		CERT_STORE_TIME_VALIDITY_FLAG 
		;
	

	bool bCollectionStore = false;
	if ( !hCollectionStore )
	{
		CHECK_CERT_RESULT( 
			hSystemStoreCA = CertOpenSystemStore( 0, "CA" ), 
			"CertOpenStore succeeded. The CA store is open. \n", 
			"Error opening the CA store." 
			);
		
		CHECK_CERT_RESULT(	
			hSystemStoreMY = CertOpenSystemStore( 0, "MY"	),
			"CertOpenStore succeeded. The MY store is open. \n",
			"Error opening the MY store."
			);
		
		CHECK_CERT_RESULT(	
			hSystemStoreROOT = CertOpenSystemStore( 0, "ROOT"	),
			"CertOpenStore succeeded. The ROOT store is open. \n",
			"Error opening the ROOT store."
			);

		CHECK_CERT_RESULT(	
			hCollectionStore = CertOpenStore( CERT_STORE_PROV_COLLECTION, 0, 0, 0, 0 ), 
			"The collection store was opened. \n",
			"There was an error while opening the collection store!"
			);

		CertAddStoreToCollection(hCollectionStore, hSystemStoreCA, 0, 0);
		CertAddStoreToCollection(hCollectionStore, hSystemStoreMY, 0, 2);
		CertAddStoreToCollection(hCollectionStore, hSystemStoreROOT, 0, 1);
		bCollectionStore = true;
	}

	CHECK_CERT_RESULT(	
		hFileStore = CertOpenStore(
			CERT_STORE_PROV_FILENAME_A,
			MY_ENCODING_TYPE,
			NULL,
			0,
			szFileName ),
		"The file store is open. Continue.\n", 
		"The file store did not open."
		);
	
	CHECK_CERT_RESULT(	
		pTargetCert = CertEnumCertificatesInStore( hFileStore, pTargetCert),
		"A certificate is available. Continue.\n",
		"No certificate available. The store may be empty."
		);
	

	while(
		pStoredCert = CertEnumCertificatesInStore(
		hCollectionStore,
		pStoredCert
		))
	{
		if ( CertCompareCertificate(X509_ASN_ENCODING, pStoredCert->pCertInfo, pTargetCert->pCertInfo) )
		{
			bResult = CertDeleteCertificateFromStore(pStoredCert) != FALSE;
			break;
		}
	}


	//--------------------------------------------------------------------
	// Clean up memory and quit.
	
	CERT_CLOSE_CTX(   pTargetCert       , "pTargetCert"       );
	CERT_CLOSE_STORE( hFileStore        , "hFileStore"        );
	if ( bCollectionStore )
	{
		CERT_CLOSE_STORE( hSystemStoreCA    , "hSystemStoreCA"    );
		CERT_CLOSE_STORE( hSystemStoreMY    , "hSystemStoreMY"    );
		CERT_CLOSE_STORE( hSystemStoreROOT  , "hSystemStoreROOT"  );
		CERT_CLOSE_STORE( hCollectionStore  , "hCollectionStore"  );
	}
	return bResult;
}