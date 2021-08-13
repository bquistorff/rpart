#include "rpart.h"
#include "R_ext/Rdynload.h"
#include "node.h"
#include "rpartproto.h"

SEXP C_init_rpcallback(SEXP rhox, SEXP ny, SEXP nr, SEXP expr1x, SEXP expr2x);
SEXP C_rpartexp2(SEXP dtimes, SEXP seps);
SEXP C_pred_rpart(SEXP dimx, SEXP nnode, SEXP nsplit, SEXP dimc,
		SEXP nnum, SEXP nodes2, SEXP vnum, SEXP split2,
		SEXP csplit2, SEXP usesur, SEXP xdata2, SEXP xmiss2);

static const R_CallMethodDef CallEntries[] = {
    {"C_init_rpcallback", (DL_FUNC) &C_init_rpcallback, 5},
    {"C_rpart", (DL_FUNC) &C_rpart, 12},
    {"C_xpred", (DL_FUNC) &C_xpred, 15},
    {"C_rpartexp2", (DL_FUNC) &C_rpartexp2, 2},
    {"C_pred_rpart", (DL_FUNC) &C_pred_rpart, 12},
    {NULL, NULL, 0}
};

#include <Rversion.h>
void
R_init_rpart(DllInfo * dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
#if defined(R_VERSION) && R_VERSION >= R_Version(2, 16, 0)
    R_forceSymbols(dll, TRUE);
#endif
}
