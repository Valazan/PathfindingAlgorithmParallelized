#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define height 24
#define width 24
struct map {
	int **mapTerrain;
	int **distanceMap;
	};

struct point {
	int x;
	int y;
	};

struct priorityQueue {
	int x[height*width];
	int y[height*width];
	int d[height*width];
	int pointer;
	};
	
	
	
	

static void display_file(const char *file_name)
{
    FILE *f = fopen(file_name, "r");      // open the specified file

    if (f != NULL)
    {
        int c;

        while ((c = fgetc(f)) != EOF)     // read character from file until EOF
        {
            putchar(c);                   // output character
        }
        fclose(f);
    }
}	
	
static void create_map_from_file(const char *file_name, int n, struct map *map)
{
    int i,j;
    int K[n][n];
    FILE *fp = fopen(file_name, "r");      // open the specified file

   if(fp == NULL) {
	perror("Errore\n");
	exit(0);
	}


    if (fp != NULL)
    {
	for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            fscanf(fp, "%d",&K[j][i]);
        }
    }

	buildMap(map);    
    
	for(i=0 ;i<n; i++){
        for(j=0; j<n; j++){
            map->mapTerrain[i+1][n-j]=K[i][j];
        }
	}
	} 
    
    
    fclose(fp);
}	


	
	
int ManhattanDistance(xStart, yStart, xEnd, yEnd) {
		int d;
		d=abs(xStart-xEnd)+abs(yStart-yEnd);
		return d;
	}

double EuclideanDistance(xStart, yStart, xEnd, yEnd) {
		double d;
		d=sqrt(pow(xStart-xEnd,2)+pow(yStart-yEnd,2));
		return d;
		}


void sortPriorityQueue(struct priorityQueue *queue) {
		    int a;
	     	    int b;
		    int c;
		    int i;
		    int j;
		    for (i = 0; i <= queue->pointer; ++i) {
			for (j = i + 1; j <= queue->pointer; ++j) {
				if (queue->d[i] > queue->d[j])
					{
					a =  queue->d[i];
					b = queue->x[i];
					c = queue->y[i];
					queue->d[i] = queue->d[j];
					queue->x[i] = queue->x[j];
					queue->y[i] = queue->y[j];
					queue->d[j] = a;
					queue->x[j] = b;
					queue->y[j] = c;

            }

        }

    }

		}


int printMap(struct map *map) {
		int i;
		int j;
		for (j=0;j<=height;j++){
			for (i=0;i<=width;i++) {
			printf("%i", map->mapTerrain[i][height-j]);
			}
		printf("\n");
		}
		return 0;
		}



int printDistanceMap(struct map *map) {
		int i;
		int j;
		for (j=0;j<=height;j++){
			for (i=0;i<=width;i++) {
			printf("%i ", map->distanceMap[i][height-j]);
			}
		printf("\n");
		}
		return 0;
		}



int buildMap(struct map *map) {
		int i;
		int j;
		map->mapTerrain=(int **)malloc(width * sizeof(int*));
		map->distanceMap=(int**)malloc(width * sizeof(int*));
		for(i = 0; i <= width; i++) {map->mapTerrain[i] = (int *)malloc(height * sizeof(int));}
		for(i = 0; i <= width; i++) {map->distanceMap[i] = (int *)malloc(height * sizeof(int));}
		for (j=0; j<=height; j++) {
   			for (i=0; i<=width; i++) {
      			map->mapTerrain[i][j]=0;
			map->distanceMap[i][j]=0;
   			}
			}
		return 0;
}



int computeDistances(struct map *map, struct point *Currentpoint, struct point *endpoint, struct point *startpoint, struct priorityQueue *queue) {


		int d1;
		int d2;
		int d3;
		int d4;
        	int d5;
        	int d6;
		int d7;
		int d8;
		int distanceToPass=0;

		if(ManhattanDistance(Currentpoint->x, Currentpoint->y, endpoint->x, endpoint->y)==1) {
				return 0;
			}

		if (Currentpoint->x+1<=width && map->mapTerrain[Currentpoint->x+1][Currentpoint->y]!=2 && map->mapTerrain[Currentpoint->x+1][Currentpoint->y]!=3)
		{
		if (map->distanceMap[Currentpoint->x+1][Currentpoint->y]==0) {

		//printf("%i \n",  map->distanceMap[Currentpoint->x+1][Currentpoint->y]);
		d1=ManhattanDistance(Currentpoint->x+1, Currentpoint->y, endpoint->x, endpoint->y);

        	d2=ManhattanDistance(Currentpoint->x+1, Currentpoint->y, startpoint->x, startpoint->y);



		map->distanceMap[Currentpoint->x+1][Currentpoint->y]=2*d1+d2;
		distanceToPass = 2*d1+d2;


		//add all information in the priority queue
		if (queue->pointer!=0) {
		queue->pointer++;
		}
		queue->x[queue->pointer]=Currentpoint->x+1;
		queue->y[queue->pointer]=Currentpoint->y;
		queue->d[queue->pointer]=distanceToPass;
		//printf("queue pointer: %i\n", queue->pointer);
		//printf("distance inserted: %i\n",distanceToPass );
		//end of information adding

		}
		}
		

		if (Currentpoint->y+1<=height && map->mapTerrain[Currentpoint->x][Currentpoint->y+1]!=2 && map->mapTerrain[Currentpoint->x][Currentpoint->y+1]!=3)
		{
		if (map->distanceMap[Currentpoint->x][Currentpoint->y+1]==0) {

		printf("%i \n",  map->distanceMap[Currentpoint->x][Currentpoint->y+1]);
               
		d3=ManhattanDistance(Currentpoint->x, Currentpoint->y+1, endpoint->x, endpoint->y);

        	d4=ManhattanDistance(Currentpoint->x, Currentpoint->y+1, startpoint->x, startpoint->y);

		map->distanceMap[Currentpoint->x][Currentpoint->y+1]=2*d3+d4;
		distanceToPass=2*d3+d4;

		
		//add all information in the priority queue
		queue->pointer++;
		//printf("queue pointer: %i\n", queue->pointer);
		queue->x[queue->pointer]=Currentpoint->x;
		queue->y[queue->pointer]=Currentpoint->y+1;
		queue->d[queue->pointer]=distanceToPass;
		//printf("distance inserted: %i\n",distanceToPass );
		//end of information adding
		}

		}


		if (Currentpoint->x-1>=0 && map->mapTerrain[Currentpoint->x-1][Currentpoint->y]!=2 && map->mapTerrain[Currentpoint->x-1][Currentpoint->y]!=3)
		{
		if (map->distanceMap[Currentpoint->x-1][Currentpoint->y]==0) {
		d5=ManhattanDistance(Currentpoint->x-1, Currentpoint->y, endpoint->x, endpoint->y);

		//printf("%i \n",  map->distanceMap[Currentpoint->x-1][Currentpoint->y]);
        	d6=ManhattanDistance(Currentpoint->x-1, Currentpoint->y, startpoint->x, startpoint->y);
		map->distanceMap[Currentpoint->x-1][Currentpoint->y]=2*d5+d6;
		distanceToPass=2*d5+d6;


		//add all information in the priority queue
		queue->pointer++;
		//printf("queue pointer: %i\n", queue->pointer);
		queue->x[queue->pointer]=Currentpoint->x-1;
		queue->y[queue->pointer]=Currentpoint->y;
		queue->d[queue->pointer]=distanceToPass;
		//printf("distance inserted: %i\n",distanceToPass );
		//end of information adding

		}
		}


		if(Currentpoint->y-1>=0 && map->mapTerrain[Currentpoint->x][Currentpoint->y-1]!=2 && map->mapTerrain[Currentpoint->x][Currentpoint->y-1]!=3)
		{
		if (map->distanceMap[Currentpoint->x][Currentpoint->y-1]==0) {

		//printf("%i \n",  map->distanceMap[Currentpoint->x][Currentpoint->y-1]);
		d7=ManhattanDistance(Currentpoint->x, Currentpoint->y-1, endpoint->x, endpoint->y);

        	d8=ManhattanDistance(Currentpoint->x, Currentpoint->y-1, startpoint->x, startpoint->y);
		map->distanceMap[Currentpoint->x][Currentpoint->y-1]=2*d7+d8;
		distanceToPass=2*d7+d8;

		//add all information in the priority queue
		queue->pointer++;
		//printf("queue pointer: %i\n", queue->pointer);
		queue->x[queue->pointer]=Currentpoint->x;
		queue->y[queue->pointer]=Currentpoint->y-1;
		queue->d[queue->pointer]=distanceToPass;
		//printf("distance inserted: %i\n",distanceToPass );
		//end of information adding

		}
		}



		
		
		sortPriorityQueue(queue);
		//printf("%i %i %i \n", queue->d[0],  queue->x[0],  queue->y[0]);



		return 1;
	}




int moveCurrentPosition(struct map *map, struct point *Currentpoint, struct priorityQueue *queue) {


		int xNew;
		int yNew;

		xNew=queue->x[0];
		yNew=queue->y[0];
		map->mapTerrain[xNew][yNew]=3; 
		Currentpoint->x=xNew;		
		Currentpoint->y=yNew;
		queue->d[0]=height*width;

		return 0;
		}

int calculateRoute(struct map *map, struct point *Currentpoint, struct point *endpoint,struct point *startpoint, struct priorityQueue *queue) {


		while (computeDistances(map, Currentpoint, endpoint, startpoint, queue)!=0) {
			moveCurrentPosition(map, Currentpoint, queue);
            

			}
		return 0;
		}


int calculateRouteOneStep(struct map *map, struct point *Currentpoint, struct point *endpoint,struct point *startpoint, struct priorityQueue *queue) {
			if (computeDistances(map, Currentpoint, endpoint, startpoint, queue)!=0) {
			moveCurrentPosition(map, Currentpoint, queue);
			return 0;
		}
			else {
			return 1;
			}
		}

int checkOtherInstances(struct map *map, struct point *Currentpoint, int valueToCheck) {
		if (map->mapTerrain[Currentpoint->x+1][Currentpoint->y]!=valueToCheck && map->mapTerrain[Currentpoint->x][Currentpoint->y+1]!= valueToCheck 			&& map->mapTerrain[Currentpoint->x-1][Currentpoint->y]!=valueToCheck && map->mapTerrain[Currentpoint->x][Currentpoint->y-1]!=valueToCheck)
		{
		return 0;
		}
		else {
		return 1;
		}
		}
			

	
	
		


	int main() {
		struct map privateMap;
		struct map privateMap2;
		struct map sharedMap;
		struct point startPoint;
		struct point endPoint;
		struct point CurrentPosition;
		struct point CurrentPositionEnd;
		struct priorityQueue queue;
		struct priorityQueue queue2;
		int mapFile;
		int i;

        /*display_file("data.txt");*/  //reading just char from txt file

        //create_map_from_file("data.txt",10, &sharedMap);   // reading matrix (matrix just for test) from txt file



		buildMap(&sharedMap);    
		
		startPoint.x=1;
		startPoint.y=2;
		endPoint.x=20;
		endPoint.y=20;
		int instancesNotMet = 1;

		CurrentPosition.x=startPoint.x;
		CurrentPosition.y=startPoint.y;
		CurrentPositionEnd.x=endPoint.x;
		CurrentPositionEnd.y=endPoint.y;




	



		

		//calculateRoute(&map, &CurrentPosition, &endPoint, &startPoint, &queue);
		//calculateRoute(&map, &CurrentPositionEnd, &startPoint, &endPoint, &queue);
		


		

		#pragma omp parallel shared(sharedMap, instancesNotMet) 
		{
		queue.pointer=0;
		queue2.pointer=0;
		buildMap(&privateMap);  
		buildMap(&privateMap2);      
        	//create_map_from_file("data.txt",height, &privateMap);   // reading matrix (matrix just for test) from txt file
        	//create_map_from_file("data.txt",height, &privateMap2);   // reading matrix (matrix just for test) from txt file
		while(instancesNotMet) {
		#pragma omp sections
		{
		#pragma omp section
		{
		printf("instance 1\n");

		if (checkOtherInstances(&sharedMap, &CurrentPosition, 4) || calculateRouteOneStep(&privateMap, &CurrentPosition, &endPoint, &startPoint, &queue)) {
		instancesNotMet = 0;
		}
		sharedMap.mapTerrain[CurrentPosition.x][CurrentPosition.y]=3;

		}
		#pragma omp section
		{
		printf("instance 2\n");
		if (checkOtherInstances(&sharedMap, &CurrentPositionEnd, 3) || calculateRouteOneStep(&privateMap2, &CurrentPositionEnd, &startPoint, &endPoint, &queue2)) {
		instancesNotMet = 0;
		}
		sharedMap.mapTerrain[CurrentPositionEnd.x][CurrentPositionEnd.y]=4;
		}
		}

		#pragma omp barrier
		}
		}
		sharedMap.mapTerrain[startPoint.x][startPoint.y]=1;
		sharedMap.mapTerrain[endPoint.x][endPoint.y]=1;
		printMap(&sharedMap);
	
		/*printf("\n\n");
		printDistanceMap(&map);
		printf("\n\n");
		printMap(&map);
		

		
		int i;
		for(i=0; i<=queue.pointer; i++) { 
		printf("%i %i %i \n", queue.d[i],  queue.x[i],  queue.y[i] );
		}
		printf("%i", queue.pointer);*/


		return 0;
	}

