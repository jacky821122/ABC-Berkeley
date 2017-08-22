abc add "-L" in pdr command.

edit abc/src/base/abci/abc.c

:26654 add a new line and add "char * pLogFileName = NULL;"
:26657 add "L" to Extra_UtilGetopt

add the code below before "case 'h':"
case 'L':
            if ( globalUtilOptind >= argc )
            {
                Abc_Print( -1, "Command line switch \"-L\" should be followed by a file name.\n" );
                goto usage;
            }
            pLogFileName = argv[globalUtilOptind];
            globalUtilOptind++;
            break;

add the code below before "return 0;"
if ( pLogFileName )
        Abc_NtkWriteLogFile( pLogFileName, pAbc->pCex, pAbc->Status, pAbc->nFrames, "pdr" );