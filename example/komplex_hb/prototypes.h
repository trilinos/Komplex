/*******************************************************************************
 * Copyright 1995, Sandia Corporation.  The United States Government retains a *
 * nonexclusive license in this software as prescribed in AL 88-1 and AL 91-7. *
 * Export of this program may require a license from the United States         *
 * Government.                                                                 *
 ******************************************************************************/

void read_hb(char *data_file, int *proc_config,
	      int *N_global, int *n_nonzeros, 
	      double **val, int **bindx,
	      double **x, double **b, double **xexact);

void read_coo(char *data_file, int *proc_config,
	      int *N_global, int *n_nonzeros,
	      double **val, int **bindx,
	      double **x, double **b, double **xexact);


void distrib_msr_matrix(int *proc_config,
	      int N_global, int *n_nonzeros, 
           int *N_update, int **update, 
	      double **val, int **bindx,
	      double **x, double **b, double **xexact);

void distrib_vbr_matrix(int *proc_config,
	      int N_global, int N_blk_global, 
           int *n_nonzeros,  int *n_blk_nonzeros,
           int *N_update, int **update, 
	      double **val, int **indx, int **rpntr, int **cpntr,
           int **bpntr, int **bindx,
	      double **x, double **b, double **xexact);

void create_vbr(char *part_file, int *proc_config, 
                int *N_global, int *N_blk_global, 
                int *n_nonzeros, int *n_blk_nonzeros,
                int *N_update, int **update,
		      int *bindx_msr, double *val_msr,
		      double **val, int **indx, int **rpntr, int **cpntr,
		      int **bpntr, int **bindx);

double smsrres (int m, int n, 
	      double *val, int *indx, 
	      double *xlocal, double *x, double *b);

double scscres (int isym, int m, int n, 
	      double *val, int *indx, int *pntr,
	      double *x, double *b);

void  scscmv (int isym, int m, int n, 
	      double *val, int *indx, int *pntr,
	      double *x, double *b);

double svbrres (int m, int n, int m_blk,
		double *val, int *indx, int *bindx, int *rpntr,
		int *cpntr, int *bpntrb, int *bpntre,
		double *x, double *b);
