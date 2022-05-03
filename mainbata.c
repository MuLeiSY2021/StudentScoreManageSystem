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

//--------初始化--------//
void initialization();

//--------测试数据------//
void testData();

//--------学生输入------//
void stuInput();

//--------学生插入------//
void stuInsert(int index, int id, const double *scores, char *name);

//--------判断重复学生--------//
int isEqual(int id);

//--------数字输入--------//
double numInput();

//--------学科数量输入--------//
int subjCountInPut();

//--------学号输入（含纠错）-------//
int idInPut();

//--------成绩输入（含纠错）--------//
double *subjectScoreInput(double *scores);

//---------姓名输入--------//
char *nameInput();

//---------确定选择函数---------//
int decision(char askStr[2]);

//---------统计数据-------//
void calculateSubject();

//TODO:DONE*需要写
void calculateStudent();

//---------分类化--------//
void statistic();

//---------成字符串输出---------//
void toString(int i);

void prnAllInfo();
//-------------------Sort--------------------//

void sortFunction(int(*pFunction)(int preCompare, int compare, int bol_up), int bol_up);

int sortId(int preCompare, int compare, int bol_up);

int sortName(int preCompare, int compare, int bol_up);

int sortScore(int preCompare, int compare, int bol_up);

double getSumScore(int tgr);

//-------------------按学号查找-----------------//
void idSearch(int inputNum);

//-------------------按姓名查找-----------------//
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
                printf("您要查找的学号是？\n");
                idSearch((int) numInput());
                break;

            case 9:
                printf("您要查找的姓名是？\n");
                nameSearch(nameInput());
                break;

            case 10:
                statistic();
                break;

            case 11:
                prnAllInfo();
                break;

            default:
                printf("输入错误，请重新输入\n");
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
            printf("人数已满");
            break;
        }

        int inputId = idInPut();

        char *inputName = nameInput();
        printf("学号是：%d\n", inputId);
        //TODO:*DONE:添加输入各科目考试成绩
        double *inputScore = (double *) malloc(sizeof(double) * 6);
        subjectScoreInput(inputScore);
        for (int i = 0; i < subjCount; i++) {
            printf("科目%d成绩是：%.3f\n", i + 1, inputScore[i]);
        }
        printf("姓名是：%s\n", inputName);

        if (!decision("确定")) {
            continue;
        }

        int tmp_index;
        if ((tmp_index = isEqual(inputId)) != -1) {
            printf("已有该学生数据");
            if (decision("覆盖")) {
                stuCount--;
            } else {
                tmp_index = stuCount;
            }
        } else {
            tmp_index = stuCount;
        }
        stuInsert(tmp_index, inputId, inputScore, inputName);
    } while (!decision("退出"));
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
    printf("输入学科数量：\n");
    int count = (int) numInput();
    while (count < 0 || count > 6) {
        printf("输入有误，请重新输入\n");
        count = (int) numInput();
    }
    return count;
}

int idInPut() {
    printf("输入学号：\n");
    int student_ID = (int) numInput();
    while (student_ID < 0) {
        printf("输入有误，请重新输入\n");
        student_ID = (int) numInput();
    }
    return student_ID;
}

char *nameInput() {
    printf("输入姓名：\n");
    char *name = (char *) malloc(20);
    scanf("%s", name);
    getchar();
    return name;
}

double *subjectScoreInput(double *scores) {
    for (int i = 0; i < subjCount; i++) {
        printf("输入科目%d成绩：\n", i + 1);
        scores[i] = numInput();
        while (scores[i] < 0) {
            printf("输入有误，请重新输入\n");
            scores[i] = numInput();
        }
    }
    return scores;
}

int decision(char askStr[2]) {
    printf("是否%s(Y/N):\n", askStr);
    char choice = (char) getchar();
    while (choice != 'Y' && choice != 'N') {
        printf("输入错误，请重新输入\n");
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
    //TODO：DONE*统计每个课程的总分和平均分
    for (int j = 0; j < subjCount; j++) {
        double total = 0;
        for (int i = 0; i < stuCount; i++) {
            total += GET_SCORE;
        }
        printf("课程%d的总分是：%.2lf,平均分是：%.2lf\n", j + 1, total, total / stuCount);
    }
}

void calculateStudent() {
    //TODO：DONE*统计每个学生的总分和平均分
    for (int i = 0; i < stuCount; i++) {
        double total = 0;
        for (int j = 0; j < subjCount; j++) {
            total += GET_SCORE;
        }
        printf("学生%s的总分是：%.2lf,平均分是：%.2lf\n", GET_NAME, total, total / subjCount);
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
    //TODO:DONE*各科分数，总分，平均分，以及按照学科输出总分和平均分
    printf("姓名%7s---学号:%5d\n", GET_NAME, GET_ID);
    double total = 0;
    for (int j = 0; j < subjCount; j++) {
        total += GET_SCORE;
        printf("科目%d---分数：%.2lf\n", j + 1, GET_SCORE);
    }
    printf("总分：%.2lf---平均分：%.2lf\n", total, total / subjCount);
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
    //TODO:DONE*按照总分
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

//TODO:DONE*查询各科
void idSearch(int inputNum) {
    for (int i = 0; i < stuCount; i++) {
        if (GET_ID == inputNum) {
            toString(i);
            return;
        }
    }
    printf("查无此人\n");
}

void nameSearch(char *name) {
    for (int i = 0; i < stuCount; i++) {
        if (!strcmp(GET_NAME, name)) {
            toString(i);
            return;
        }
    }
    printf("查无此人\n");
}

//TODO:DONE对每门课程分别统计每个类别的人数以及所占百分比
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
        printf("课程%d:\n", j + 1);
        printf("优秀(90~100):%d人 占比%.2f%%\n", excellent, 100 * (float) excellent / (float) stuCount);
        printf("良好(80~89) :%d人 占比%.2f%%\n", good, 100 * (float) good / (float) stuCount);
        printf("中等(70~79) :%d人 占比%.2f%%\n", medium, 100 * (float) medium / (float) stuCount);
        printf("及格(60~69) :%d人 占比%.2f%%\n", pass, 100 * (float) pass / (float) stuCount);
        printf("不及格(0~59):%d人 占比%.2f%%\n", gg, 100 * (float) gg / (float) stuCount);
    }
}