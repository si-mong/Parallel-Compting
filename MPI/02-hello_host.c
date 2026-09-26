#include <stdio.h>
#include <mpi.h>
int main(int argc, char argv[])
{
	int ver, subver;
	int nRank, nProcs;
	char procName[MPI_MAX_PROCESSOR_NAME]; 	 /* OpenMPI = 256 */
	int nNameLen;

	MPI_Init(NULL, NULL); 						/* MPI start */
	MPI_Comm_rank(MPI_COMM_WORLD, &nRank); 	/* get current processor rank id */
	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);  /* get number of processors */
	
	MPI_Get_version(&ver, &subver); 				/* MPI version information */
	
	// execute on rank 0
	if(nRank == 0) 
		printf("MPI Version %d.%d\n", ver, subver);
	
	MPI_Get_processor_name(procName, &nNameLen);

	printf("Hello World.(Process name = %s, nRank = %d, nProcs = %d)\n",procName, nRank, nProcs);
	MPI_Finalize();
	return 0;
}
