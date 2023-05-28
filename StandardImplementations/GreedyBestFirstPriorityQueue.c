#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define height 1000
#define width 1000
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


		int d1;
		int d2;
		int d3;
		int d4;



		
		if (Currentpoint->x+1<=width && map->mapTerrain[Currentpoint->x+1][Currentpoint->y]!=2 && map->distanceMap[Currentpoint->x+1][Currentpoint->y]==0) {
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


			if(d1==0) {
				return 0;
			}
		}
		if (Currentpoint->y-1>=0 && map->mapTerrain[Currentpoint->x][Currentpoint->y-1]!=2 && map->distanceMap[Currentpoint->x][Currentpoint->y-1]==0) {
		d2=ManhattanDistance(Currentpoint->x, Currentpoint->y-1, endpoint->x, endpoint->y);
		map->distanceMap[Currentpoint->x][Currentpoint->y-1]=d2;

		//add all information in the priority queue
		queue->pointer=queue->pointer+1;
		queue->x[queue->pointer]=Currentpoint->x;
		queue->y[queue->pointer]=Currentpoint->y-1;
		queue->d[queue->pointer]=d2;
		//end of information adding

			if(d2==0) {
				return 0;
			}
		}
		if (Currentpoint->x-1>=0 && map->mapTerrain[Currentpoint->x-1][Currentpoint->y]!=2 && map->distanceMap[Currentpoint->x-1][Currentpoint->y]==0) {
		d3=ManhattanDistance(Currentpoint->x-1, Currentpoint->y, endpoint->x, endpoint->y);
		map->distanceMap[Currentpoint->x-1][Currentpoint->y]=d3;


		//add all information in the priority queue
		queue->pointer=queue->pointer+1;
		queue->x[queue->pointer]=Currentpoint->x-1;
		queue->y[queue->pointer]=Currentpoint->y;
		queue->d[queue->pointer]=d3;
		//end of information adding

			if(d3==0) {
				return 0;
			}
		}
		if (Currentpoint->y+1<=height && map->mapTerrain[Currentpoint->x][Currentpoint->y+1]!=2 && map->distanceMap[Currentpoint->x][Currentpoint->y+1]==0) {
		d4=ManhattanDistance(Currentpoint->x, Currentpoint->y+1, endpoint->x, endpoint->y);
		map->distanceMap[Currentpoint->x][Currentpoint->y+1]=d4;

		//add all information in the priority queue
		queue->pointer=queue->pointer+1;
		queue->x[queue->pointer]=Currentpoint->x;
		queue->y[queue->pointer]=Currentpoint->y+1;
		queue->d[queue->pointer]=d4;
		//end of information adding


			if(d4==0) {
				return 0;
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
		map->mapTerrain[xNew][yNew]=3;  //when i move the current position to a new location, i mark that location in the mapTerrain putting a 3, in this way i 
		Currentpoint->x=xNew;		//could avoid to compute again distances from a position
		Currentpoint->y=yNew;
		queue->d[0]=height*width;

		return 0;
		}

int calculateRoute(struct map *map, struct point *Currentpoint, struct point *endpoint, struct priorityQueue *queue) {
		while (computeDistances(map, Currentpoint, endpoint, queue)!=0) {
			moveCurrentPosition(map, Currentpoint, queue);

			}
		return 0;
		}
			

	
	
		


	int main() {
		struct map map;
		struct point startPoint;
		struct point endPoint;
		struct point CurrentPosition;
		struct priorityQueue queue;
		int mapFile;
		int i;


		

		queue.pointer=0;
		startPoint.x=1;
		startPoint.y=5;
		endPoint.x=10;
		endPoint.y=10;
		CurrentPosition.x=startPoint.x;
		CurrentPosition.y=startPoint.y;
		
		buildMap(&map);

		map.mapTerrain[startPoint.x][startPoint.y]=1;
		map.mapTerrain[endPoint.x][endPoint.y]=1;
		calculateRoute(&map, &CurrentPosition, &endPoint, &queue);
	
		/*printf("\n\n");
		printDistanceMap(&map);
		printf("\n\n");
		printMap(&map);*/
		

		
		/*int i;
		for(i=0; i<=queue.pointer; i++) { 
		printf("%i %i %i \n", queue.d[i],  queue.x[i],  queue.y[i] );
		}
		printf("%i", queue.pointer);*/


		return 0;
	}

