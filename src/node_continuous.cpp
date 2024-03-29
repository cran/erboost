// The code is a modified version of gbm library originally written by Greg Ridgeway. See
// 
// Ridgeway, G. (2007). Generalized boosted models: A guide to the gbm package. R pack-
// age vignette. http://cran.r-project.org/web/packages/gbm.
//------------------------------------------------------------------------------
//  by Greg Ridgeway  Copyright (C) 2003
#include "node_continuous.h"
#include "node_factory.h"

CNodeContinuous::CNodeContinuous()
{
    dSplitValue = 0.0;
}


CNodeContinuous::~CNodeContinuous()
{
    #ifdef NOISY_DEBUG
    Rprintf("continuous destructor\n");
    #endif
}



erboostRESULT CNodeContinuous::PrintSubtree
(
    unsigned long cIndent
)
{
    erboostRESULT hr = erboost_OK;
    unsigned long i = 0;
    
    for(i=0; i< cIndent; i++) Rprintf("  ");
    Rprintf("N=%f, Improvement=%f, Prediction=%f, NA pred=%f\n",
           dTrainW,
           dImprovement,
           dPrediction,
           (pMissingNode == NULL ? 0.0 : pMissingNode->dPrediction));

    for(i=0; i< cIndent; i++) Rprintf("  ");
    Rprintf("V%ld < %f\n",
           iSplitVar,
           dSplitValue);
    hr = pLeftNode->PrintSubtree(cIndent+1);

    for(i=0; i< cIndent; i++) Rprintf("  ");
    Rprintf("V%ld > %f\n",
           iSplitVar,
           dSplitValue);
    hr = pRightNode->PrintSubtree(cIndent+1);

    return hr;
}



signed char CNodeContinuous::WhichNode
(
    CDataset *pData,
    unsigned long iObs
)
{
    signed char ReturnValue = 0;
    double dX = pData->adX[iSplitVar*(pData->cRows) + iObs];

    if(!ISNA(dX))
    {
        if(dX < dSplitValue)
        {
            ReturnValue = -1;
        }
        else
        {
            ReturnValue = 1;
        }
    }
    // if missing value returns 0

    return ReturnValue;
}


signed char CNodeContinuous::WhichNode
(
    double *adX,
    unsigned long cRow,
    unsigned long cCol,
    unsigned long iRow
)
{
    signed char ReturnValue = 0;
    double dX = adX[iSplitVar*cRow + iRow];

    if(!ISNA(dX))
    {
        if(dX < dSplitValue)
        {
            ReturnValue = -1;
        }
        else
        {
            ReturnValue = 1;
        }
    }
    // if missing value returns 0

    return ReturnValue;
}



erboostRESULT CNodeContinuous::RecycleSelf
(
    CNodeFactory *pNodeFactory
)
{
    erboostRESULT hr = erboost_OK;
    pNodeFactory->RecycleNode(this);
    return hr;
};



erboostRESULT CNodeContinuous::TransferTreeToRList
(
    int &iNodeID,
    CDataset *pData,
    int *aiSplitVar,
    double *adSplitPoint,
    int *aiLeftNode,
    int *aiRightNode,
    int *aiMissingNode,
    double *adErrorReduction,
    double *adWeight,
    double *adPred,
    VEC_VEC_CATEGORIES &vecSplitCodes,
    int cCatSplitsOld,
    double dShrinkage
)
{
    erboostRESULT hr = erboost_OK;
    int iThisNodeID = iNodeID;

    aiSplitVar[iThisNodeID] = iSplitVar;
    adSplitPoint[iThisNodeID] = dSplitValue;
    adErrorReduction[iThisNodeID] = dImprovement;
    adWeight[iThisNodeID] = dTrainW;
    adPred[iThisNodeID] = dShrinkage*dPrediction;


    iNodeID++;
    aiLeftNode[iThisNodeID] = iNodeID;
    hr = pLeftNode->TransferTreeToRList(iNodeID,
                                        pData,
                                        aiSplitVar,
                                        adSplitPoint,
                                        aiLeftNode,
                                        aiRightNode,
                                        aiMissingNode,
                                        adErrorReduction,
                                        adWeight,
                                        adPred,
                                        vecSplitCodes,
                                        cCatSplitsOld,
                                        dShrinkage);
    if(erboost_FAILED(hr)) goto Error;

    aiRightNode[iThisNodeID] = iNodeID;
    hr = pRightNode->TransferTreeToRList(iNodeID,
                                         pData,
                                         aiSplitVar,
                                         adSplitPoint,
                                         aiLeftNode,
                                         aiRightNode,
                                         aiMissingNode,
                                         adErrorReduction,
                                         adWeight,
                                         adPred,
                                         vecSplitCodes,
                                         cCatSplitsOld,
                                         dShrinkage);
    if(erboost_FAILED(hr)) goto Error;

    aiMissingNode[iThisNodeID] = iNodeID;
    hr = pMissingNode->TransferTreeToRList(iNodeID,
                                           pData,
                                           aiSplitVar,
                                           adSplitPoint,
                                           aiLeftNode,
                                           aiRightNode,
                                           aiMissingNode,
                                           adErrorReduction,
                                           adWeight,
                                           adPred,
                                           vecSplitCodes,
                                           cCatSplitsOld,
                                           dShrinkage);
    if(erboost_FAILED(hr)) goto Error;

Cleanup:
    return hr;
Error:
    goto Cleanup;
}


