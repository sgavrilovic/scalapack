#include <stdlib.h>
#include <stdio.h>

#ifndef Int
#define Int int
#endif
void Cblacs_gridinfo(int ConTxt, int *nprow, int *npcol, int *myrow, int *mycol);

void Cblacs_abort(int ConTxt, int ErrNo);

void Cblacs_get(int ConTxt, int what, int *val);

void Cblacs_gridmap(int *ConTxt, int *usermap, int ldup, int nprow0, int npcol0);

Int SL_Cgridreshape(ctxt, pstart, row_major_in, row_major_out, P, Q)
Int ctxt, pstart, row_major_in, row_major_out, P, Q;
{
   Int Cblacs_pnum();
   Int nctxt, P0, Q0, Np, i, *g;

   Cblacs_gridinfo(ctxt, &P0, &Q0, &i, &Np);
   Np = P * Q;
   if (Np+pstart > P0*Q0)
   {
      fprintf(stderr, "Illegal reshape command in %s\n",__FILE__);
      Cblacs_abort(ctxt, -22);
   }
   g = (Int *) malloc(Np * sizeof(Int));
   if (!g)
   {
      fprintf(stderr, "Cannot allocate memory in %s\n",__FILE__);
      Cblacs_abort(ctxt, -23);
   }
   if (row_major_in)  /* Read in in row-major order */
   {
      if (row_major_out)
	 for (i=0; i != Np; i++)
            g[(i%Q)*P+i/Q] = Cblacs_pnum(ctxt, (pstart+i)/Q0, (pstart+i)%Q0);
      else
	 for (i=0; i != Np; i++)
            g[i] = Cblacs_pnum(ctxt, (pstart+i)/Q0, (pstart+i)%Q0);
   }
   else /* read in in column-major order */
   {
      if (row_major_out)
	 for (i=0; i != Np; i++)
            g[(i%Q)*P+i/Q] = Cblacs_pnum(ctxt, (pstart+i)%P0, (pstart+i)/P0);
      else
	 for (i=0; i != Np; i++)
            g[i] = Cblacs_pnum(ctxt, (pstart+i)%P0, (pstart+i)/P0);
   }
   Cblacs_get(ctxt, 10, &nctxt);
   Cblacs_gridmap(&nctxt, g, P, P, Q);
   free(g);

   return(nctxt);
}

Int sl_gridreshape_(ctxt, pstart, row_major_in, row_major_out, P, Q)
Int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}

Int SL_GRIDRESHAPE(ctxt, pstart, row_major_in, row_major_out, P, Q)
Int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}

Int sl_gridreshape__(ctxt, pstart, row_major_in, row_major_out, P, Q)
Int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}

Int sl_gridreshape(ctxt, pstart, row_major_in, row_major_out, P, Q)
Int *ctxt, *pstart, *row_major_in, *row_major_out, *P, *Q;
{
   return( SL_Cgridreshape(*ctxt, *pstart, *row_major_in, *row_major_out,
                           *P, *Q) );
}
