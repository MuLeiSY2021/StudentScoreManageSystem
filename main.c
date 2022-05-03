#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GET_ID *((int *)(student[i]))
#define GET_SCORE *((double *)(student[i] + sizeof(int )))
#define GET_NAME *((char **)(student[i] + sizeof(int) + sizeof(double )))

static char **student;
static int stuNum;
static double sum[2];

//--------------FUNCTION------------------//

//--------��ʼ��--------//
void initialization();

//--------��������------//
void testData();

//--------ѧ������------//
void stuInput();

//--------ѧ������------//
void stuInsert(int index, int id, double score, char *name);

//--------�ж��ظ�ѧ��--------//
int isEqual(int id);

//--------��������--------//
double numInput();

//--------ѧ�����루������-------//
int idInPut();

//--------�ɼ����루������--------//
double scoreInput();

//---------��������--------//
char *nameInput();

//---------ȷ��ѡ����---------//
int decision(char askStr[2]);

//---------ͳ������-------//
double *calculate();

//---------���໯--------//
void statistic();

//---------���ַ������---------//
void toString();

//-------------------Sort--------------------//

void sortFunction(int(*pFunction)(int preCompare, int compare, int bol_up), int bol_up);

int sortId(int preCompare, int compare, int bol_up);

int sortName(int preCompare, int compare, int bol_up);

int sortScore(int preCompare, int compare, int bol_up);

//-------------------��ѧ�Ų���-----------------//
void idSearch(int inputNum);

//-------------------����������-----------------//
void nameSearch(char *name);

//--------------------MAIN-----------------//
int main() {
    setbuf(stdout, 0);
    initialization();

    for (;;) {
        char mainFace[][45] =
                {
                        "Input record\n",
                        "Calculate total and average score of course\n",
                        "Sort in descending order by score\n",
                        "Sort in ascending order by score\n",
                        "Sort in ascending order by number\n",
                        "Sort in dictionary order by name\n",
                        "Search by number\n",
                        "Search by name\n",
                        "Statistic analysis\n",
                        "List record\n",
                };
        for (int i = 0; i < sizeof(mainFace) / 45; i++) {
            printf("%d.%s", i + 1, mainFace[i]);
        }
        printf("0.Exit\n");
        printf("Please enter your choice(number):\n");
        int chi = (int) (numInput());
        switch (chi) {
            case 0:
                return 0;

            case 1:
                stuInput();
                break;

            case 2:
                calculate();
                printf("�γ̵��ܷ��ǣ�%.2f,ƽ�����ǣ�%.2f\n", sum[0], sum[1]);
                break;

            case 3:
                sortFunction(sortScore, 0);
                break;

            case 4:
                sortFunction(sortScore, 1);
                break;

            case 5:
                sortFunction(sortId, 1);
                break;

            case 6:
                sortFunction(sortName, 0);
                break;

            case 7:
                printf("��Ҫ���ҵ�ѧ���ǣ�\n");
                idSearch((int) numInput());
                break;

            case 8:
                printf("��Ҫ���ҵ������ǣ�\n");
                nameSearch(nameInput());
                break;

            case 9:
                statistic();
                break;

            case 10:
                toString();
                break;

            default:
                printf("�����������������\n");
                break;
        }
    }
}

void initialization() {
    student = (char **) malloc(30 * 8);
    for (int i = 0; i < 30; ++i) {
        student[i] = (char *) malloc(21);
    }
    testData();
}


void testData() {
    srand(time(NULL));
    stuNum = (rand() % 15 + 15);
    for (int i = 0; i < stuNum; i++) {
        GET_ID = rand() % 1000 + 500;
        GET_SCORE = (double) (rand() % 10000) / 100.0;
        int max = rand() % 3 + 4;
        char *tmp_name = (char *) malloc(max + 1);
        for (int j = 0; j < max; j++) {
            tmp_name[j] = (char) (rand() % (123 - 97) + 97);
            if (j == 0) {
                tmp_name[j] -= 'a' - 'A';
            }
        }
        tmp_name[max] = '\0';
        GET_NAME = tmp_name;
    }
}

void stuInput() {
    do {
        if (stuNum == 30) {
            printf("��������");
            break;
        }

        int inputId = idInPut();
        double inputScore = scoreInput();
        char *inputName = nameInput();
        printf("ѧ���ǣ�%d\n", inputId);
        printf("�ɼ��ǣ�%.3f\n", inputScore);
        printf("�����ǣ�%s\n", inputName);

        if (!decision("ȷ��")) {
            continue;
        }

        int tmp_index;
        if ((tmp_index = isEqual(inputId)) != -1) {
            printf("���и�ѧ������");
            if (decision("����")) {
                stuNum--;
            } else {
                tmp_index = stuNum;
            }
        } else {
            tmp_index = stuNum;
        }
        stuInsert(tmp_index, inputId, inputScore, inputName);
    } while (!decision("�˳�"));
}

void stuInsert(int index, int id, double score, char *name) {
    int i = index;
    GET_ID = id;
    GET_SCORE = score;
    GET_NAME = name;
    stuNum++;
}

double numInput() {
    char nums[50];
    scanf("%s", &nums);
    getchar();
    char *ptr;
    double num = strtod(nums, &ptr);
    if (num == 0) {
        int flg = 0;
        for (int i = 0; i < strlen(ptr); ++i) {
            if (ptr[i] != 0) {
                flg = 1;
            }
        }
        if (flg) {
            return -1;
        }
    }
    return num;
}

int idInPut() {
    printf("����ѧ�ţ�\n");
    int student_ID = (int) numInput();
    while (student_ID < 0) {
        printf("������������������\n");
        student_ID = (int) numInput();
    }
    return student_ID;
}

char *nameInput() {
    printf("����������\n");
    char *name = (char *) malloc(20);
    scanf("%s", name);
    getchar();
    return name;
}

double scoreInput() {
    printf("����ɼ���\n");
    double score = numInput();
    while (score < 0) {
        printf("������������������\n");
        score = numInput();
    }
    return score;
}

int decision(char askStr[2]) {
    printf("�Ƿ�%s(Y/N):\n", askStr);
    char choice = (char) getchar();
    while (choice != 'Y' && choice != 'N') {
        printf("�����������������\n");
        while (choice != '\n') {
            choice = (char) getchar();
        }
        choice = (char) getchar();
    }
    getchar();
    if (choice == 'Y') {
        return 1;
    } else {
        return 0;
    }
}

double *calculate() {
    for (int i = 0; i < stuNum; i++) {
        sum[0] += GET_SCORE;
    }
    sum[1] = sum[0] / (double) stuNum;
    return sum;
}

int isEqual(int id) {
    for (int i = 0; i < stuNum; ++i) {
        if (GET_ID == id) {
            return i;
        }
    }
    return -1;
}

void toString() {
    for (int i = 0; i < stuNum; i++) {
        printf("����%7s---ѧ��:%5d---����:%.3lf\n", GET_NAME, GET_ID, GET_SCORE);
    }
}

void sortFunction(int(*pFunction)(int preCompare, int compare, int bol_up), int bol_up) {
    if (stuNum < 2) {
        return;
    }

    //insert Sort
    for (int unsortedIndex = 1; unsortedIndex < stuNum; unsortedIndex++) {
        char *tmp_stu = NULL;
        for (int sortedIndex = 0; sortedIndex < unsortedIndex; sortedIndex++) {
            if ((*pFunction)(unsortedIndex, sortedIndex, bol_up) && !tmp_stu) {
                tmp_stu = student[unsortedIndex];
                sortedIndex--;
                continue;
            } else if (tmp_stu) {
                char *tmp_preStu = student[sortedIndex];
                student[sortedIndex] = tmp_stu;
                tmp_stu = tmp_preStu;
            }
        }
    }
}

int sortId(int preCompare, int compare, int bol_up) {
    int i = preCompare;
    int tmp = GET_ID;
    i = compare;
    return bol_up ? tmp < GET_ID : tmp > GET_ID;
}

int sortName(int preCompare, int compare, int bol_up) {
    int i = preCompare;
    char *tmp = GET_NAME;
    i = compare;
    return bol_up ? strcmp(tmp, GET_NAME) < 0 : strcmp(tmp, GET_NAME) > 0;
}

int sortScore(int preCompare, int compare, int bol_up) {
    int i = preCompare;
    double tmp = GET_SCORE;
    i = compare;
    return bol_up ? tmp < GET_SCORE : tmp > GET_SCORE;
}

void idSearch(int inputNum) {
    for (int i = 0; i < stuNum; i++) {
        if (GET_ID == inputNum) {
            printf("���ҽ��������%s---ѧ��:%5d---����:%.3lf\n", GET_NAME, GET_ID, GET_SCORE);
            return;
        }
    }
    printf("���޴���\n");
}

void nameSearch(char *name) {
    for (int i = 0; i < stuNum; i++) {
        if (!strcmp(GET_NAME, name)) {
            printf("���ҽ��������:%s---ѧ��:%5d---����:%.3lf\n", GET_NAME, GET_ID, GET_SCORE);
            return;
        }
    }
    printf("���޴���\n");
}

void statistic() {
    int excellent = 0, good = 0, medium = 0, pass = 0, gg = 0;
    if (stuNum < 1) {
        return;
    }
    for (int i = 0; i < stuNum; i++) {
        if (GET_SCORE <= 100 && GET_SCORE >= 90) {
            excellent++;
            continue;
        } else if (GET_SCORE < 90 && GET_SCORE >= 80) {
            good++;
            continue;
        } else if (GET_SCORE < 80 && GET_SCORE >= 70) {
            medium++;
            continue;
        } else if (GET_SCORE < 70 && GET_SCORE >= 60) {
            pass++;
            continue;
        } else if (GET_SCORE < 60) {
            gg++;
            continue;
        }
    }
    printf("����(90~100):%d�� ռ��%.2f%%\n", excellent, 100 * (float) excellent / (float) stuNum);
    printf("����(80~89) :%d�� ռ��%.2f%%\n", good, 100 * (float) good / (float) stuNum);
    printf("�е�(70~79) :%d�� ռ��%.2f%%\n", medium, 100 * (float) medium / (float) stuNum);
    printf("����(60~69) :%d�� ռ��%.2f%%\n", pass, 100 * (float) pass / (float) stuNum);
    printf("������(0~59):%d�� ռ��%.2f%%\n", gg, 100 * (float) gg / (float) stuNum);
}