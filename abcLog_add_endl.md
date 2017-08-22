abc add "\n" when writing log files.

edit abc/src/base/abci/abcLog.c

:113 

for ( i = pCex->nRegs; i < pCex->nBits; i++ )
	fprintf( pFile, "%d", Abc_InfoHasBit(pCex->pData,i) );

/*-----------replaced with------------*/

int j = 1;
for ( i = pCex->nRegs; i < pCex->nBits; i++ )
{
	if(i == pCex->nRegs + j * pCex->nPis && j != 0)
	{
		fprintf( pFile, "\n" );
		j++;
	}
	fprintf( pFile, "%d", Abc_InfoHasBit(pCex->pData,i) );
}

