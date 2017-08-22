/**CPPFile****************************************************************

  FileName    [NZL.cpp]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Network and node package.]

  Synopsis    [Command file.]

  Author      [Jacky Hsieh]

  Affiliation [NTU]

  Date        [july 6 , 2017.]

***********************************************************************/

// #include "my_Print.h"
#include "cstdlib"
#include "iostream"
#include "stack"
#include "map"
#include "base/abc/abc.h"
#include "base/main/mainInt.h"
#include "misc/vec/vecPtr.h"
#include "sat/cnf/cnf.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

static int my_print3(Abc_Frame_t * pAbc, int argc, char **argv);

////////////////////////////////////////////////////////////////////////
///                     FUNCTION DEFINITIONS                         ///
////////////////////////////////////////////////////////////////////////

/**Function*************************************************************

  Synopsis    [Start / Stop the NZL package]

  Description []

  SideEffects []

  SeeAlso     []

***********************************************************************/

extern "C"
{
	void NZL_Init3(Abc_Frame_t * pAbc)
	{
		Cmd_CommandAdd( pAbc, "Nian-Ze Lee", "myp3", my_print3, 0);
	}
	void NZL_End3(Abc_Frame_t * pAbc) {}
  Aig_Man_t * Abc_NtkToDar( Abc_Ntk_t * pNtk, int fExors, int fRegisters );
  void * Cnf_DataWriteIntoSolver( Cnf_Dat_t * p, int nFrames, int fInit );
  int sat_solver_solve(sat_solver* s, lit* begin, lit* end, ABC_INT64_T nConfLimit, ABC_INT64_T nInsLimit, ABC_INT64_T nConfLimitGlobal, ABC_INT64_T nInsLimitGlobal);
}


/**Function*************************************************************

  Synopsis    [Print ID, Lv, Fanin, Fanout of all nodes]

  Description []

  SideEffects []

  SeeAlso     []

***********************************************************************/

void DFS3(Abc_Obj_t *obj, Vec_Ptr_t *vPi, map<int, bool> isMaxNtk_tmp);

int my_print3(Abc_Frame_t * pAbc, int argc, char **argv)
{
  Abc_Ntk_t *pNtk = pAbc->pNtkCur;
  Aig_Man_t *pAig = Abc_NtkToDar(pNtk, 0, 0);
  Cnf_Dat_t *pCnf = Cnf_DeriveSimple(pAig, 0);
  sat_solver *solver = (sat_solver*)Cnf_DataWriteIntoSolver(pCnf, 1, 0);

  return 0;
}

void DFS3(Abc_Obj_t *obj, Vec_Ptr_t *vPi, map<int, bool> isMaxNtk_tmp)
{
  Abc_Obj_t *pFanin;
  int i;
  if(Abc_NodeIsTravIdCurrent(obj)){
    return;
  }
  // Vec_PtrPush(vNodeTmp, obj);
  Abc_NodeSetTravIdCurrent(obj);
  if(Abc_ObjIsPi(obj) == 1){
    Vec_PtrPush(vPi, obj);
    return;
  }
  Abc_ObjForEachFanin(obj, pFanin, i){
      DFS3(pFanin, vPi, isMaxNtk_tmp);
  }
}