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

using namespace std;

////////////////////////////////////////////////////////////////////////
///                        DECLARATIONS                              ///
////////////////////////////////////////////////////////////////////////

static int my_print(Abc_Frame_t * pAbc, int argc, char **argv);

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
	void NZL_Init(Abc_Frame_t * pAbc)
	{
		Cmd_CommandAdd( pAbc, "Nian-Ze Lee", "myp", my_print, 0);
	}

	void NZL_End(Abc_Frame_t * pAbc)
	{
	}	
}


/**Function*************************************************************

  Synopsis    [Print ID, Lv, Fanin, Fanout of all nodes]

  Description []

  SideEffects []

  SeeAlso     []

***********************************************************************/

void DFS(Abc_Obj_t *obj, Vec_Ptr_t *vPi, map<int, bool> isMaxNtk_tmp);

int my_print(Abc_Frame_t * pAbc, int argc, char **argv)
{
  Abc_Ntk_t *pNtk = pAbc->pNtkCur;
  Abc_Obj_t *pPo, *current, *maxPo;
  Vec_Ptr_t *maxPi = Vec_PtrAlloc(Vec_PtrSize(pNtk->vPis));
  // Vec_Ptr_t *vNode = Vec_PtrAlloc(Abc_NtkObjNum(pNtk));
  map<int, bool> isMaxNtk;

  int i, j, max = 0;
  Abc_NtkForEachPo(pNtk, pPo, i)
  {
    Vec_Ptr_t *vPi = Vec_PtrAlloc(Vec_PtrSize(pNtk->vPis));
    // Vec_Ptr_t *vNodeTmp = Vec_PtrAlloc(Abc_NtkObjNum(pNtk));
    map<int, bool> isMaxNtk_tmp;
    Abc_NtkIncrementTravId(pNtk);
    DFS(pPo, vPi, isMaxNtk_tmp);
    // cout << "Current Po: " << pPo->Id << "  Pi: ";
    // Vec_PtrForEachEntry(Abc_Obj_t*, vPi, current, j)
    // {
      // cout << current->Id << " ";
    // }
    // cout << endl;
    if(Vec_PtrSize(vPi) > max)
    {
      max = Vec_PtrSize(vPi);
      Vec_PtrCopy(maxPi, vPi);
      // Vec_PtrCopy(vNode, vNodeTmp);
      maxPo = pPo;
    }
    Vec_PtrFree(vPi);
    // Vec_PtrFree(vNodeTmp);
  }
  // cout << "Current Po: " << maxPo->Id << "  Pi: ";
  // Vec_PtrForEachEntry(Abc_Obj_t*, maxPi, current, j)
  // {
  //   cout << current->Id << " ";
  // }
  // cout << endl;
  // cout << Vec_PtrSize(vNode) - Vec_PtrSize(maxPi) << endl;
  
  Abc_Ntk_t * pAig;
  pAig = Abc_NtkAlloc( ABC_NTK_STRASH, ABC_FUNC_AIG, 1 );
  Abc_Obj_t *pNewPi;
  Vec_PtrForEachEntry(Abc_Obj_t*, maxPi, current, j)
  {
    pNewPi = Abc_NtkCreatePi(pAig);
    
  }

  Vec_PtrFree(maxPi);
  // Vec_PtrFree(vNode);

  return 0;
}

void DFS(Abc_Obj_t *obj, Vec_Ptr_t *vPi, map<int, bool> isMaxNtk_tmp)
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
      DFS(pFanin, vPi, isMaxNtk_tmp);
  }
}