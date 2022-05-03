#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GET_ID *((int *)(student[i]))
#define GET_NAME *((char **)(student[i] + sizeof(int)))
#define GET_SCORE *((double *)(student[i] + sizeof(int) + sizeof(char *) + j * sizeof (double )))


static char **student;
static int stuCount;
static int subjCount = -1;

//--------------FUNCTION------------------//

//--------��ʼ��--------//
void initialization();

//--------��������------//
void testData();

//--------ѧ������------//
void stuInput();

//--------ѧ������------//
void stuInsert(int index, int id, const double *scores, char *name);

//--------�ж��ظ�ѧ��--------//
int isEqual(int id);

//--------��������--------//
double numInput();

//--------ѧ����������--------//
int subjCountInPut();

//--------ѧ�����루������-------//
int idInPut();

//--------�ɼ����루������--------//
double *subjectScoreInput(double *scores);

//---------��������--------//
char *nameInput();

//---------ȷ��ѡ����---------//
int decision(char askStr[2]);

//---------ͳ������-------//
void calculateSubject();

//TODO:DONE*��Ҫд
void calculateStudent();

//---------���໯--------//
void statistic();

//---------���ַ������---------//
void toString(int i);

void prnAllInfo();
//-------------------Sort--------------------//

void sortFunction(int(*pFunction)(int preCompare, int compare, int bol_up), int bol_up);

int sortId(int preCompare, int compare, int bol_up);

int sortName(int preCompare, int compare, int bol_up);

int sortScore(int preCompare, int compare, int bol_up);

double getSumScore(int tgr);

//-------------------��ѧ�Ų���-----------------//
void idSearch(int inputNum);

//-------------------����������-----------------//
void nameSearch(char *name);

//--------------------MAIN-----------------//
int main() {
    setbuf(stdout, 0);
    subjCount = subjCountInPut();
    initialization();


    for (;;) {
        char mainFace[][60] =
                {
                        "Input record\n",
                        "Calculate total and average score of every course\n",
                        "Calculate total and average score of every student\n",
                        "Sort in descending order by total score of every student\n",
                        "Sort in ascending order by total score of every student\n",
                        "Sort in ascending order by number\n",
                        "Sort in dictionary order by name\n",
                        "Search by number\n",
                        "Search by name\n",
                        "Statistic analysis for every course\n",
                        "List record\n",
                };
        for (int i = 0; i < sizeof(mainFace) / 60; i++) {
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
                calculateSubject();
                break;

            case 3:
                calculateStudent();
                break;

            case 4:
                sortFunction(sortScore, 0);
                break;

            case 5:
                sortFunction(sortScore, 1);
                break;

            case 6:
                sortFunction(sortId, 1);
                break;

            case 7:
                sortFunction(sortName, 0);
                break;

            case 8:
                printf("��Ҫ���ҵ�ѧ���ǣ�\n");
                idSearch((int) numInput());
                break;

            case 9:
                printf("��Ҫ���ҵ������ǣ�\n");
                nameSearch(nameInput());
                break;

            case 10:
                statistic();
                break;

            case 11:
                prnAllInfo();
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
        student[i] = (char *) malloc(sizeof(int) + sizeof(char *) + sizeof(double) * 6);
    }
    testData();
}


void testData() {
    if (subjCount != -1) {
        subjCount = (rand() % 6) + 1;
    }
    stuCount = (rand() % 15 + 15);
    srand(time(NULL));
    for (int i = 0; i < stuCount; i++) {
        GET_ID = rand() % 10000 + 500;

        for (int j = 0; j < subjCount; j++) {
            GET_SCORE = (double) ((rand() % 7000) + 3000) / 100.0;
        }

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
        if (stuCount == 30) {
            printf("��������");
            break;
        }

        int inputId = idInPut();

        char *inputName = nameInput();
        printf("ѧ���ǣ�%d\n", inputId);
        //TODO:*DONE:����������Ŀ���Գɼ�
        double *inputScore = (double *) malloc(sizeof(double) * 6);
        subjectScoreInput(inputScore);
        for (int i = 0; i < subjCount; i++) {
            printf("��Ŀ%d�ɼ��ǣ�%.3f\n", i + 1, inputScore[i]);
        }
        printf("�����ǣ�%s\n", inputName);

        if (!decision("ȷ��")) {
            continue;
        }

        int tmp_index;
        if ((tmp_index = isEqual(inputId)) != -1) {
            printf("���и�ѧ������");
            if (decision("����")) {
                stuCount--;
            } else {
                tmp_index = stuCount;
            }
        } else {
            tmp_index = stuCount;
        }
        stuInsert(tmp_index, inputId, inputScore, inputName);
    } while (!decision("�˳�"));
}

void stuInsert(int index, int id, const double *scores, char *name) {
    int i = index;
    GET_ID = id;
    GET_NAME = name;
    for (int j = 0; j < subjCount; j++) {
        GET_SCORE = scores[j];
    }
    stuCount++;
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

int subjCountInPut() {
    printf("����ѧ��������\n");
    int count = (int) numInput();
    while (count < 0 || count > 6) {
        printf("������������������\n");
        count = (int) numInput();
    }
    return count;
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

double *subjectScoreInput(double *scores) {
    for (int i = 0; i < subjCount; i++) {
        printf("�����Ŀ%d�ɼ���\n", i + 1);
        scores[i] = numInput();
        while (scores[i] < 0) {
            printf("������������������\n");
            scores[i] = numInput();
        }
    }
    return scores;
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

void calculateSubject() {
    //TODO��DONE*ͳ��ÿ���γ̵��ֺܷ�ƽ����
    for (int j = 0; j < subjCount; j++) {
        double total = 0;
        for (int i = 0; i < stuCount; i++) {
            total += GET_SCORE;
        }
        printf("�γ�%d���ܷ��ǣ�%.2lf,ƽ�����ǣ�%.2lf\n", j + 1, total, total / stuCount);
    }
}

void calculateStudent() {
    //TODO��DONE*ͳ��ÿ��ѧ�����ֺܷ�ƽ����
    for (int i = 0; i < stuCount; i++) {
        double total = 0;
        for (int j = 0; j < subjCount; j++) {
            total += GET_SCORE;
        }
        printf("ѧ��%s���ܷ��ǣ�%.2lf,ƽ�����ǣ�%.2lf\n", GET_NAME, total, total / subjCount);
    }
}

int isEqual(int id) {
    for (int i = 0; i < stuCount; ++i) {
        if (GET_ID == id) {
            return i;
        }
    }
    return -1;
}

void toString(int i) {
    //TODO:DONE*���Ʒ������ܷ֣�ƽ���֣��Լ�����ѧ������ֺܷ�ƽ����
    printf("����%7s---ѧ��:%5d\n", GET_NAME, GET_ID);
    double total = 0;
    for (int j = 0; j < subjCount; j++) {
        total += GET_SCORE;
        printf("��Ŀ%d---������%.2lf\n", j + 1, GET_SCORE);
    }
    printf("�ܷ֣�%.2lf---ƽ���֣�%.2lf\n", total, total / subjCount);
}

void prnAllInfo() {
    for (int i = 0; i < stuCount; i++) {
        toString(i);
    }
    calculateSubject();
}

void sortFunction(int(*pFunction)(int preCompare, int compare, int bol_up), int bol_up) {
    if (stuCount < 2) {
        return;
    }

    //insert Sort
    for (int unsortedIndex = 1; unsortedIndex < stuCount; unsortedIndex++) {
        for (int sortedIndex = unsortedIndex; sortedIndex > 0; sortedIndex--) {
            if ((*pFunction)(sortedIndex, sortedIndex - 1, bol_up)) {
                break;
            } else {
                char *tmp_preStu = student[sortedIndex];
                student[sortedIndex] = student[sortedIndex - 1];
                student[sortedIndex - 1] = tmp_preStu;
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
    //TODO:DONE*�����ܷ�
    double tmp = getSumScore(preCompare);
    return bol_up ? tmp < getSumScore(compare) : tmp > getSumScore(compare);
}

double getSumScore(int tgr) {
    int i = tgr;
    double total = 0;
    for (int j = 0; j < subjCount; j++) {
        total += GET_SCORE;
    }
    return total;
}

//TODO:DONE*��ѯ����
void idSearch(int inputNum) {
    for (int i = 0; i < stuCount; i++) {
        if (GET_ID == inputNum) {
            toString(i);
            return;
        }
    }
    printf("���޴���\n");
}

void nameSearch(char *name) {
    for (int i = 0; i < stuCount; i++) {
        if (!strcmp(GET_NAME, name)) {
            toString(i);
            return;
        }
    }
    printf("���޴���\n");
}

//TODO:DONE��ÿ�ſγ̷ֱ�ͳ��ÿ�����������Լ���ռ�ٷֱ�
void statistic() {
    if (stuCount < 1) {
        return;
    }
    for (int j = 0; j < subjCount; j++) {
        int excellent = 0, good = 0, medium = 0, pass = 0, gg = 0;
        for (int i = 0; i < stuCount; i++) {
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
        printf("�γ�%d:\n", j + 1);
        printf("����(90~100):%d�� ռ��%.2f%%\n", excellent, 100 * (float) excellent / (float) stuCount);
        printf("����(80~89) :%d�� ռ��%.2f%%\n", good, 100 * (float) good / (float) stuCount);
        printf("�е�(70~79) :%d�� ռ��%.2f%%\n", medium, 100 * (float) medium / (float) stuCount);
        printf("����(60~69) :%d�� ռ��%.2f%%\n", pass, 100 * (float) pass / (float) stuCount);
        printf("������(0~59):%d�� ռ��%.2f%%\n", gg, 100 * (float) gg / (float) stuCount);
    }
}