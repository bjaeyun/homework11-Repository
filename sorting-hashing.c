/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);
int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command; 
	int *array = NULL; //int형 포인터 변수 array 선언 후 NULL로 초기화
	int *hashtable = NULL; //int형 포인터 변수 hashtable 선언 후 NULL로 초기화
	int key = -1;	
	int index = -1; 

	srand(time(NULL)); //

	do{	
		printf("-------------------[Byeun jaeyun] [2022041046]------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); 

		switch(command) { 
		case 'z': case 'Z':	//z or Z일때
			initialize(&array); //initialize함수 호출
			break;
		case 'q': case 'Q':	//q or Q일때
			freeArray(array); //freeArray함수 호출
			break;
		case 's': case 'S': //s or S일때
			selectionSort(array); //selectionSort함수 호출
			break;
		case 'i': case 'I': //i or I일때
			insertionSort(array); //insertionSort함수 호출
			break;
		case 'b': case 'B': //b or B일때
			bubbleSort(array); //bubbleSort함수 호출
			break;
		case 'l': case 'L': //l or L일때
			shellSort(array); //shellSort함수 호출
			break;
		case 'k': case 'K': //k or K일때
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //printArray함수 호출
			quickSort(array, MAX_ARRAY_SIZE); //quickSort함수 호출
			printf("----------------------------------------------------------------\n");
			printArray(array); //printArray함수 호출
			break;
		case 'h': case 'H': //h or H일때
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //printArray함수 호출
			hashing(array, &hashtable); //hashing함수 호출
			printArray(hashtable); //printArray함수 호출
			break;
		case 'e': case 'E': //e or E일때
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable); //printArray함수 호출
			index = search(hashtable, key); //index에 search함수 호출
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;
		case 'p': case 'P': //p or P일떄
			printArray(array); //printArray함수 호출
			break;
		default: //command가 잘못 입력 되었을때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1; //1반환
}


int initialize(int** a)//배열을 초기화 하는 함수
{
	int *temp = NULL;//int형 포인터변수 temp 선언후 초기화
	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { // a가 가리키는 값이 NULL인 경우
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); // temp에 int형 요소 MAX_ARRAY_SIZE개를 가지는 메모리를 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else // a가 가리키는 값이 NULL이 아닌 경우
		temp = *a; //temp에 a가 가리키는 값을 복사

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; // 배열의 각 요소에 0부터 MAX_ARRAY_SIZE-1 사이의 랜덤값을 저장

	return 0; //0 반환
}

int freeArray(int *a) //배열을 free하는 함수
{
	if(a != NULL) //a가 비어있지않을때
		free(a);	//a를 free
	return 0;	//0 반환
}

void printArray(int *a) //배열을 출력하는 함수
{
	if (a == NULL) {//a가 비어있을때
		printf("nothing to print.\n"); //오류메시지 출력
		return;	//NULL값 반환
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)	//MAX_ARRAY_SIZE만큼 반복하는 for문
		printf("a[%02d] ", i); 	//배열출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)	//MAX_ARRAY_SIZE만큼 반복하는 for문
		printf("%5d ", a[i]);
	printf("\n");
}

int selectionSort(int *a)//선택정렬 함수
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //현재 배열의 상태를 출력

	//min값을 찾아 최소값 부터 앞으로 정렬하는 방식
	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 최소값의 인덱스를 i로 초기화
		min = a[i]; // 최소값을 a[i]로 초기화
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j])	// 현재 최소값보다 작은 값을 찾으면
			{
				min = a[j]; // 해당 값을 최소값으로 저장
				minindex = j; // 해당 값의 인덱스를 최소값 인덱스에 저장
			}
		}
		a[minindex] = a[i]; // 최소값의 자리에 현재 값 저장
		a[i] = min; // 현재 위치에 최소값 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}


int insertionSort(int *a)//삽입정렬 함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 현재 배열의 상태를 출력

	//앞에서부터 반복하며 알맞은 자리에 삽입하는 방식
	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; // 삽입할 값을 t에 저장
		j = i;
		while (a[j-1] > t && j > 0)  // 현재 값보다 큰 값이 나올 때까지 왼쪽으로 이동하면서 비교
		{
			a[j] = a[j-1]; // 값이 크면 오른쪽으로 한 칸 이동
			j--; //j 감소
		}
		a[j] = t; // 삽입할 값을 알맞은 자리에 삽입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 배열의 상태를 출력

	return 0;
}


int bubbleSort(int *a)//버블정렬 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 현재 배열의 상태를 출력

	//근접값을 비교하며 정렬하는 방식
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) // 현재 값과 다음 값 비교하여 순서가 잘못되어 있다면
			{
				//배열 값 스왑
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 배열의 상태를 출력

	return 0;
}

int shellSort(int *a)//셀정렬 함수
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); // 현재 배열의 상태를 출력합니다.

	// 임의의 간격을 생성해 간격별로 정렬하며 간격을 줄여나가는 방식
	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; // 현재 값 저장
				k = j;
				while (k > h - 1 && a[k - h] > v) // 현재 값보다 이전 간격의 값이 큰 경우
				{
					a[k] = a[k - h]; // 이전 간격의 값을 현재 위치로 이동
					k -= h;
				}
				a[k] = v; // 현재 값을 알맞은 위치에 삽입
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); // 정렬된 배열의 상태를 출력합니다.

	return 0;
}

int quickSort(int *a, int n)//퀵정렬 함수
{
	int v, t;
	int i, j;

	//pivot을 설정해 pivot을 기준으로 정렬해 나가는 방식
	if (n > 1)
	{
		v = a[n-1]; // pivot으로 사용할 값을 선택
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v); // pivot보다 큰 값을 찾을 때까지 i를 증가
			while(a[--j] > v); // pivot보다 작은 값을 찾을 때까지 j를 감소

			if (i >= j) break; // i와 j가 교차하면 반복문을 종료
            // a[i]와 a[j]의 값을 교환
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

        // pivot을 기준으로 분할된 두 개의 부분 배열에 대해 재귀적으로 퀵정렬을 수행
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}


int hashCode(int key) {//key 값을 구해 반환하는 함수
   return key % MAX_HASH_TABLE_SIZE;
}


int hashing(int *a, int **ht)//hasing 함수
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //만약 hashtable[hashcode]가 -1인 경우
		{
			hashtable[hashcode] = key; //해당 인덱스에 key 값을 저장
		} else 	{ //그렇지 않은 경우 충돌이 발생한 것이므로 선형 탐색을 통해 다음 빈 슬롯찾기

			index = hashcode; //index를 hashcode로 초기화

			while(hashtable[index] != -1) //hashtable[index]가 -1이 아닐 때까지
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //빈 슬롯을 찾은 후에는 해당 인덱스에 key 값을 저장
		}
	}

	return 0;
}

int search(int *ht, int key)//hash-search 함수
{
	int index = hashCode(key); // key의 해시코드를 구함

	if(ht[index] == key) // 해당 인덱스의 값이 key와 일치하는 경우
		return index; // 인덱스를 반환

	while(ht[++index] != key) // 일치하는 값이 나올 때까지 다음 인덱스로 이동하면서 탐색
	{
		index = index % MAX_HASH_TABLE_SIZE; // 인덱스를 순환적으로 처리하기 위해 해시 테이블의 크기로 나눈 나머지를 구함
	}
	return index; // 일치하는 값의 인덱스를 반환
}