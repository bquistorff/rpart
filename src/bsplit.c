/*
 * The routine which will find the best split for a node
 *
 * Input :      node
 *              node number
 *
 * Output:      Fills in the node's
 *                      primary splits
 *                      competitor splits
 */
#include "rpart.h"
#include "node.h"
#include "rpartproto.h"

void
bsplit(pNode me, int n1, int n2, int n1_te, int n2_te)
{
    int i, j, k, k_te;
    int kk;
    int nc;
    double improve;
    double split = 0.0;
    pSplit tsplit;
    int *index, *index_te;
    double *xtemp, *xtemp_te;              /* these 3 because I got tired of typeing
				 * "rp.xtemp", etc */
    double **ytemp;
    double *wtemp;

    xtemp = rp.xtemp;
	xtemp_te = rp.xtemp_te;
    ytemp = rp.ytemp;
    wtemp = rp.wtemp;

    /*
     * test out the variables 1 at at time
     */
    me->primary = (pSplit) NULL;
    for (i = 0; i < rp.nvar; i++) {
		index = rp.sorts[i];
		index_te = rp.sorts_te[i];
		nc = rp.numcat[i];
		/* extract x and y data */
		k = 0;
		for (j = n1; j < n2; j++) {
			kk = index[j];
			if (kk >= 0 && rp.wt[kk] > 0) {  /* x data not missing and wt > 0 */
				xtemp[k] = rp.xdata[i][kk];
				ytemp[k] = rp.ydata[kk];
				wtemp[k] = rp.wt[kk];
				k++;
			}
		}

		if (k == 0 || (nc == 0 && xtemp[0] == xtemp[k - 1]))
			continue;           /* no place to split */

		k_te = 0;
		for (j = n1_te; j < n2_te; j++) {
			kk = index_te[j];
			if (kk >= 0) {  /* x data not missing and wt > 0 */
				xtemp_te[k_te] = rp.xdata_te[i][kk];
				k_te++;
			}
		}

		(*rp_choose) (k, k_te, ytemp, xtemp, xtemp_te, nc, rp.min_node, rp.min_node_te, &improve,
				&split, rp.csplit, me->risk, wtemp);

		/*
		* Originally, this just said "if (improve > 0)", but rounding
		* error will sometimes create a non zero that should be 0.  Yet we
		* want to retain invariance to the scale of "improve".
		*/
		if (improve > rp.iscale)
			rp.iscale = improve;        /* largest seen so far */
		if (improve > (rp.iscale * 1e-10)) {
			improve /= rp.vcost[i];     /* scale the improvement */
			tsplit = insert_split(&(me->primary), nc, improve, rp.maxpri);
			if (tsplit) {
			tsplit->improve = improve;
			tsplit->var_num = i;
			tsplit->spoint = split;
			tsplit->count = k;
			if (nc == 0) {
				tsplit->spoint = split;
				tsplit->csplit[0] = rp.csplit[0];
			} else
				for (k = 0; k < nc; k++)
				tsplit->csplit[k] = rp.csplit[k];
			}
		}
    }
}
