#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define height 100
#define width 100
struct map {
	int **mapTerrain;
	int **distanceMap;
	};

struct point {
	int x;
	int y;
	};

struct priorityQueue {
	int x[10000];
	int y[10000];
	int d[10000];
	int pointer;
	};

int read_file(char route[]) {
	int dim=10;
	char c[1000];

	/*if(mapFile==NULL) {
	perror("Errore allocazione\n");
	exit(0);
	} */
	FILE *fp;
	fp=fopen(route, "r");
	if (fp==NULL) {
	perror("Errore di apertura file");
	exit(0);
	}


	fscanf(fp, "%[^\n]", c);
	printf("Data from the file:\n%s", c);
	fscanf(fp, "%[^\n]", c);
	printf("Data from the file:\n%s", c);

			/*if (i>=dim) {
			dim*=2;
			mapFile=realloc(mapFile, sizeof(mapFile)*dim);
			}*/
		
		
		return 0;
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


int computeDistances(struct map *map, struct point *Currentpoint, struct point *endpoint, struct priorityQueue *queue) {


		int d1=0;
		int d2=0;
		int d3=0;
		int d4=0;


		#pragma omp parallel
		{

		#pragma omp sections
		{
		#pragma omp section 
		{
		//if else, in order to make distances, that has been already calculated, available for everyone
		if (Currentpoint->x+1<=width && map->distanceMap[Currentpoint->x+1][Currentpoint->y]==0){
		
			if (Currentpoint->x+1<=width && map->mapTerrain[Currentpoint->x+1][Currentpoint->y]!=2) {
			d1=ManhattanDistance(Currentpoint->x+1, Currentpoint->y, endpoint->x, endpoint->y);
			map->distanceMap[Currentpoint->x+1][Currentpoint->y]=d1;

			//add all information in the priority queue
			if (queue->pointer!=0) {
			queue->pointer=queue->pointer+1;
			}
			queue->x[queue->pointer]=Currentpoint->x+1;
			queue->y[queue->pointer]=Currentpoint->y;
			queue->d[queue->pointer]=d1;
			//end of information adding
			}
		}
		//the distance is already be computed and then it is transferred in the priority queue
		else {
			if (queue->pointer!=0) {
			queue->pointer=queue->pointer+1;
			}
			d1=map->distanceMap[Currentpoint->x+1][Currentpoint->y];
			queue->x[queue->pointer]=Currentpoint->x+1;
			queue->y[queue->pointer]=Currentpoint->y;
			queue->d[queue->pointer]=map->distanceMap[Currentpoint->x+1][Currentpoint->y];
			}
			

		}
		
		#pragma omp section 
		{
		if (Currentpoint->y-1>=0 && map->distanceMap[Currentpoint->x][Currentpoint->y-1]==0) {

			if (Currentpoint->y-1>=0 && map->mapTerrain[Currentpoint->x][Currentpoint->y-1]!=2) {
			d2=ManhattanDistance(Currentpoint->x, Currentpoint->y-1, endpoint->x, endpoint->y);
			map->distanceMap[Currentpoint->x][Currentpoint->y-1]=d2;

			//add all information in the priority queue
			queue->pointer=queue->pointer+1;
			queue->x[queue->pointer]=Currentpoint->x;
			queue->y[queue->pointer]=Currentpoint->y-1;
			queue->d[queue->pointer]=d2;
			//end of information adding
			}
		}
		else {
			//add all information in the priority queue
			d2=map->distanceMap[Currentpoint->x][Currentpoint->y-1];
			queue->pointer=queue->pointer+1;
			queue->x[queue->pointer]=Currentpoint->x;
			queue->y[queue->pointer]=Currentpoint->y-1;
			queue->d[queue->pointer]=map->distanceMap[Currentpoint->x][Currentpoint->y-1];
			}
		
		}


			
		#pragma omp section 
		{
		if (Currentpoint->x-1>=0 && map->distanceMap[Currentpoint->x-1][Currentpoint->y]==0){

			if (Currentpoint->x-1>=0 && map->mapTerrain[Currentpoint->x-1][Currentpoint->y]!=2) {
			d3=ManhattanDistance(Currentpoint->x-1, Currentpoint->y, endpoint->x, endpoint->y);
			map->distanceMap[Currentpoint->x-1][Currentpoint->y]=d3;


			//add all information in the priority queue
			queue->pointer=queue->pointer+1;
			queue->x[queue->pointer]=Currentpoint->x-1;
			queue->y[queue->pointer]=Currentpoint->y;
			queue->d[queue->pointer]=d3;
			//end of information adding
			}
		}
		else {
			d3=map->distanceMap[Currentpoint->x-1][Currentpoint->y];
			queue->pointer=queue->pointer+1;
			queue->x[queue->pointer]=Currentpoint->x-1;
			queue->y[queue->pointer]=Currentpoint->y;
			queue->d[queue->pointer]=map->distanceMap[Currentpoint->x-1][Currentpoint->y];
			}
		}

		
		#pragma omp section 
		{
		if (Currentpoint->y+1<=height && map->distanceMap[Currentpoint->x][Currentpoint->y+1]==0 ) {

			if (Currentpoint->y+1<=height && map->mapTerrain[Currentpoint->x][Currentpoint->y+1]!=2 ) {
			d4=ManhattanDistance(Currentpoint->x, Currentpoint->y+1, endpoint->x, endpoint->y);
			map->distanceMap[Currentpoint->x][Currentpoint->y+1]=d4;

			//add all information in the priority queue
			queue->pointer=queue->pointer+1;
			queue->x[queue->pointer]=Currentpoint->x;
			queue->y[queue->pointer]=Currentpoint->y+1;
			queue->d[queue->pointer]=d4;
			//end of information adding
			}
		}
		else {
			//add all information in the priority queue
			d4=map->distanceMap[Currentpoint->x][Currentpoint->y+1];
			queue->pointer=queue->pointer+1;
			queue->x[queue->pointer]=Currentpoint->x;
			queue->y[queue->pointer]=Currentpoint->y+1;
			queue->d[queue->pointer]=map->distanceMap[Currentpoint->x][Currentpoint->y+1];
			//end of information adding
		}
		

		}
		}
		}

			if(d1==0) {
				return 0;
			}
			if(d2==0) {
				return 0;
			}
			if(d3==0) {
				return 0;
			}
			if(d4==0) {
				return 0;
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
		
		//if (map->mapTerrain[xNew][yNew]!=3){
		#pragma omp barrier		
		//map->mapTerrain[xNew][yNew]=3;  //when i move the current position to a new location, i mark that location in the mapTerrain putting a 3, in this way I 
		Currentpoint->x=xNew;		//could avoid to compute again distances from a position
		Currentpoint->y=yNew;
		queue->d[0]=height*width;
		printf("position moved at %i, %i\n", xNew, yNew);
		
		/*}
		else {
		xNew=queue->x[1];
		yNew=queue->y[1];
		map->mapTerrain[xNew][yNew]=3;  //when i move the current position to a new location, i mark that location in the mapTerrain putting a 3, in this way i 
		Currentpoint->x=xNew;		//could avoid to compute again distances from a position
		Currentpoint->y=yNew;
		queue->d[1]=height*width;
		}*/

		return 0;
		}

int calculateRoute(struct map *map, struct point *Currentpoint, struct point *endpoint, struct priorityQueue *queue) {
		while (computeDistances(map, Currentpoint, endpoint, queue)!=0) {
			moveCurrentPosition(map, Currentpoint, queue);
			}
		return 0;
		}

int calculateRouteOneStep(struct map *map, struct point *Currentpoint, struct point *endpoint, struct priorityQueue *queue) {
			if(computeDistances(map, Currentpoint, endpoint, queue) != 0) {
			moveCurrentPosition(map, Currentpoint, queue);
			return 0;
			}
			else
			{
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
		struct map map;
		struct point startPoint;
		struct point endPoint;
		struct point CurrentPosition;
		struct point CurrentPositionEnd;
		struct point CurrentPosition2;
		struct point CurrentPosition3;
		struct point CurrentPosition4;
		struct priorityQueue queue;
		struct priorityQueue queueParallel;
		struct priorityQueue queueParallel2;
		int mapFile;



		

		queue.pointer=0;
		queueParallel2.pointer=0;
		startPoint.x=1;
		startPoint.y=3;
		endPoint.x=80;
		endPoint.y=80;
		CurrentPosition.x=startPoint.x;
		CurrentPosition.y=startPoint.y;
		CurrentPositionEnd.x=endPoint.x;
		CurrentPositionEnd.y=endPoint.y;



		
		buildMap(&map);

		map.mapTerrain[startPoint.x][startPoint.y]=1;
		map.mapTerrain[endPoint.x][endPoint.y]=1;
		/*map.mapTerrain[2][2]=2;
		map.mapTerrain[3][2]=2;
		map.mapTerrain[4][2]=2;
		map.mapTerrain[4][3]=2;
		map.mapTerrain[4][4]=2;
		map.mapTerrain[4][5]=2;
		map.mapTerrain[4][6]=2;
		map.mapTerrain[3][6]=2;*/



		//calculateRoute(&map, &CurrentPosition, &endPoint, &queue);



		/*int i;
		for(i=0; i<=queue.pointer; i++) { 
		printf("%i %i %i \n", queue.d[i],  queue.x[i],  queue.y[i] );
		}
		printf("%i", queue.pointer);


		

		CurrentPosition3.x=3;
		CurrentPosition3.y=1; */

	

		//calculateRoute(&map, &CurrentPosition, &endPoint, &queueParallel);


		int instancesNotMet = 1;

		 
		#pragma omp parallel shared(map, CurrentPosition, CurrentPositionEnd) private(queueParallel)
		{
		queueParallel.pointer=0;
		while(instancesNotMet) 
		{
		#pragma omp sections
		{
		#pragma omp section
		{
		if(calculateRouteOneStep(&map, &CurrentPosition, &CurrentPositionEnd, &queueParallel) || checkOtherInstances(&map, &CurrentPosition, 4)) {
		instancesNotMet = 0;
		printf("instances are met: %i\n", instancesNotMet);
		}
		map.mapTerrain[CurrentPosition.x][CurrentPosition.y]=3;
		}
		#pragma omp section
		{
		if(calculateRouteOneStep(&map, &CurrentPositionEnd, &CurrentPosition, &queueParallel) || checkOtherInstances(&map, &CurrentPositionEnd, 3)) {
		instancesNotMet = 0;
		printf("instances are met: %i\n", instancesNotMet);
		}
		map.mapTerrain[CurrentPositionEnd.x][CurrentPositionEnd.y]=4;
		}
		}
		}
		}




	
		//printf("\n\n");
		//printDistanceMap(&map);
		printf("\n\n");
		printMap(&map);
		

		
		


		return 0;
	}

