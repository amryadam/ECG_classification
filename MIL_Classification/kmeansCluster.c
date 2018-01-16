#include "mex.h" // ʹ��MEX�ļ����������ͷ�ļ�
#include <stdio.h>
#include <time.h>
#include<stdlib.h>


// ִ�о��幤����C����
double computeDistance( double* inst, double* centers, int dim )
{
    double distance = 0;
    int k;
    for( k=0; k<dim; k++)
    {
        distance += ((inst[k]-centers[k])*(inst[k]-centers[k]));
    }
    return distance;
}
void Cluster(double* data, double* output, int k, int M, int N)
{
	int i, j, temp;
    int *select;
	//����������״̬
    int complete = 0;
    int iterNum = 0;
    int *clusters;
    int *clusterNum;
    
    double **tempCenter;
	double **inst;
	double **centers;
    double **distance;
    
	inst = (double **)malloc(sizeof(double *)*M);
    for( i = 0; i < M; i++ )
        inst[i]=(double *)malloc(sizeof(double)*N);

	centers = (double **)malloc(sizeof(double *)*k);
	for( i = 0; i < k; i++ )
		centers[i] = (double *)malloc(sizeof(double)*N);

    distance = (double **)malloc(sizeof(double *)*M);
    for( i = 0; i < M; i++ )
        distance[i]=(double *)malloc(sizeof(double)*k);
    
    clusters = (int *)malloc(sizeof(int)*M);
    clusterNum = (int *)malloc(sizeof(int)*k);
    
    tempCenter = (double **)malloc(sizeof(double *)*k);
    for( i = 0; i < k; i++ )
        tempCenter[i] = (double *)malloc(sizeof(double)*N);
    
    select = (int *)malloc(sizeof(int)*k);
    //copy data
	for( i = 0; i < M; i++ )
		for( j = 0; j < N; j++ )
			inst[i][j] = *( data + j*M + i );
	
	
	srand( (unsigned)time( NULL ) );  
    //��ʼ��k��center
    for( i = 0; i < k; i++)
	{
		temp = (int)(M*rand()/(RAND_MAX+1.0));
		for( j = 0; j < i; j++ )
		{
            if( *(select+j) == temp )
			{
				j = 0;
				temp = (int)(M*rand()/(RAND_MAX+1.0));
				continue;
			}
		}
		*(select+i) = temp;
	}
    
    
    for(i = 0; i<k; i++)
	{
	    for(j = 0; j<N; j++)
            centers[i][j] = inst[select[i]][j];
	}
    
  
    //EM�㷨
    while( complete==0 )
    {
        
        //����������
        for(i = 0; i < M; i++)
		{
            for(j = 0; j < k; j++)
			{
                *(*(distance+i)+j) = computeDistance(inst[i],centers[j],N);
            }
		}
      
        //M
        //ͳ�Ƹ������������ʼ��
         for(i=0; i<k; i++)
            clusterNum[i] = 0;
        
        for(i = 0; i < M; i++)
        {
            double nearest = 1.79769e+308;
            for(j = 0; j<k; j++)
            {
               if( distance[i][j] < nearest)
               {
                   nearest = distance[i][j];
                   clusters[i] = j;
               }
            }
            clusterNum[clusters[i]]++;
         }
        //��ʼ���µľ�������
        for(i = 0;i < k; i++)
            for( j=0; j<N; j++)
                tempCenter[i][j] = 0;
        //�����µľ�������
        for(i = 0; i< M; i++)
        {
            for(j = 0; j < N; j++)
            {
                tempCenter[clusters[i]][j] += inst[i][j];
            }
        }
		
        for( i = 0; i < k; i++ )
        {
            for( j = 0; j < N; j++)
            { 
                if( clusterNum[i] != 0)
                    tempCenter[i][j] /= clusterNum[i];
                else
                    tempCenter[i][j] = centers[i][j];
            }
        }
        //�ж��Ƿ���ֹ
        complete = 1;
        for(i = 0; i < k; i++)
        {
            for(j = 0; j < N; j++)
            {
                if( tempCenter[i][j] != centers[i][j] )
                {
                    complete = 0;
                    break;
                }
            }
        }

		if( complete == 1 )
		{
			for( i = 0; i < k; i++ )
				for( j = 0; j < N; j++ )
					 *( output + j*k + i ) = centers[i][j];
		}
        //����centers
        for(i = 0; i < k; i++)
            for(j = 0; j < N; j++)
                centers[i][j] = tempCenter[i][j];
        //iter

        iterNum++;
    }
    
	for( i = 0; i < M; i++ ) 
		free(*(inst+i));
	free(inst);

	for( i = 0; i < k; i++ )
		free(*(centers+i));
	free(centers);
   
    for( i = 0; i < M; i++ )
        free(*(distance+i));
    free(distance);
    
    free(clusters);
    free(clusterNum);
    
    for( i = 0; i < k; i++ )
        free(*(tempCenter+i));
    free(tempCenter);
    
    free(select);

}
// MEX�ļ��ӿں���
void mexFunction(int nlhs,mxArray *plhs[], int nrhs,const mxArray *prhs[])
{
    double *output;
    double *instMatrix;
	double *tempCenters;
    int k, M, N;
    instMatrix = mxGetPr(prhs[0]);
	k = (int)*(mxGetPr(prhs[1]));
	M = mxGetM(prhs[0]);
	N = mxGetN(prhs[0]);
    plhs[0] = mxCreateDoubleMatrix(k, N, mxREAL);
    output = mxGetPr(plhs[0]);
   
	
    Cluster(instMatrix, output, k, M, N);

}