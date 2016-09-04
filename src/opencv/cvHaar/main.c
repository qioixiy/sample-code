#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct CvRect
{
	int top;
	int bootom;
	int width;
	int height;
}
CvRect;

typedef struct CvSize
{
	int x;
	int y;
}
CvSize;

#define CV_HAAR_FEATURE_MAX  3

typedef struct CvHaarFeature
{
    int  tilted;
    struct
    {
        CvRect r;
        float weight;
    } rect[CV_HAAR_FEATURE_MAX];
}
CvHaarFeature;

int GetSize_CvHaarFeature() {
	return sizeof (CvHaarFeature);
}

typedef struct CvHaarClassifier
{
    int count;
    CvHaarFeature* haar_feature;
    float* threshold;
    int* left;
    int* right;
    float* alpha;
}
CvHaarClassifier;
int GetSize_CvHaarClassifier(int CvHaarFeature_Count) {
	return sizeof(CvHaarClassifier) + CvHaarFeature_Count * GetSize_CvHaarFeature();
}

typedef struct CvHaarStageClassifier
{
    int  count;
    float threshold;
    CvHaarClassifier* classifier;

    int next;
    int child;
    int parent;
}
CvHaarStageClassifier;

int GetSize_CvHaarStageClassifier(int CvHaarClassifier_Count, 
								  int CvHaarFeature_Count) {
	return sizeof(CvHaarStageClassifier) 
		+ CvHaarClassifier_Count * GetSize_CvHaarClassifier(CvHaarFeature_Count);
}

typedef struct CvHidHaarClassifierCascade CvHidHaarClassifierCascade;

typedef struct CvHaarClassifierCascade
{
    int  flags;
    int  count;
    CvSize orig_window_size;
    CvSize real_window_size;
    double scale;
    CvHaarStageClassifier* stage_classifier;
    CvHidHaarClassifierCascade* hid_cascade;
}
CvHaarClassifierCascade;
int GetSize_HaarClassifierCascade(
	int CvHaarStageClassifier_Count,
	int CvHaarClassifier_Count,
	int CvHaarFeature_Count) {
	
	return sizeof(CvHaarClassifierCascade)
		+ CvHaarStageClassifier_Count
		* GetSize_CvHaarStageClassifier(CvHaarClassifier_Count, CvHaarFeature_Count);
	
}

unsigned char Init_CvHaarClassifierCascade(
	CvHaarClassifierCascade* p,
	int CvHaarStageClassifier_Count,
	int CvHaarClassifier_Count,
	int CvHaarFeature_Count) {
	
	p->count = CvHaarStageClassifier_Count;
	p->stage_classifier = (CvHaarStageClassifier *)&p[1];
	
	for (int size_CvHaarStageClassifier = 0; 
		 size_CvHaarStageClassifier < CvHaarStageClassifier_Count;
		 size_CvHaarStageClassifier++) {
		
		CvHaarStageClassifier *pCvHaarStageClassifier = p->stage_classifier;
		CvHaarClassifier *pCvHaarClassifier = (CvHaarClassifier *)&pCvHaarStageClassifier[CvHaarStageClassifier_Count];
		
		pCvHaarStageClassifier[size_CvHaarStageClassifier].count = CvHaarClassifier_Count;
		pCvHaarStageClassifier[size_CvHaarStageClassifier].classifier = &pCvHaarClassifier[CvHaarClassifier_Count
																							* size_CvHaarStageClassifier];
		
		for (int size_CvHaarClassifier = 0;
			 size_CvHaarClassifier < CvHaarClassifier_Count;
			 size_CvHaarClassifier++) {
			CvHaarClassifier *pCvHaarClassifier = pCvHaarStageClassifier[size_CvHaarStageClassifier].classifier;
			CvHaarFeature *pCvHaarFeature = (CvHaarFeature *)&pCvHaarClassifier[CvHaarStageClassifier_Count * CvHaarClassifier_Count];


			pCvHaarClassifier[size_CvHaarClassifier].count = CvHaarFeature_Count;
			pCvHaarClassifier[size_CvHaarClassifier].haar_feature = &pCvHaarFeature[CvHaarFeature_Count
																					* size_CvHaarClassifier];
		}
		
	}
}

CvHaarClassifierCascade* New_CvHaarClassifierCascade(
	int CvHaarStageClassifier_Count,
	int CvHaarClassifier_Count,
	int CvHaarFeature_Count) {
	
	int Size_HaarClassifierCascade = GetSize_HaarClassifierCascade(
		CvHaarStageClassifier_Count,
		CvHaarClassifier_Count,
		CvHaarFeature_Count);
	printf("size:%d\n", Size_HaarClassifierCascade);

	CvHaarClassifierCascade* pCvHaarClassifierCascade = malloc(Size_HaarClassifierCascade);
	memset(pCvHaarClassifierCascade, 0, Size_HaarClassifierCascade);

	Init_CvHaarClassifierCascade(pCvHaarClassifierCascade,
								 CvHaarStageClassifier_Count,
								 CvHaarClassifier_Count,
								 CvHaarFeature_Count);
	
	return pCvHaarClassifierCascade;
}
#define P(x) printf(#x":%d\n", x)
void SettingCvHaarClassifierCascade(CvHaarClassifierCascade *pCvHaarClassifierCascade) {

	P(pCvHaarClassifierCascade->count);

	for (int i = 0; i< pCvHaarClassifierCascade->count; i++) {
		P(pCvHaarClassifierCascade->stage_classifier[i].count);

		for (int j = 0; j < pCvHaarClassifierCascade->stage_classifier[i].count; j++) {
			P(pCvHaarClassifierCascade->stage_classifier[i].classifier[j].count);
		}
	}		
}


int main() {
	
	printf("CvHaarFeature size: %d\n", sizeof (CvHaarFeature) );
	printf("CvHaarClassifier size: %d\n", sizeof (CvHaarClassifier) );
	printf("CvHaarStageClassifier size: %d\n", sizeof (CvHaarStageClassifier) );
	printf("CvHaarClassifierCascade size: %d\n", sizeof (CvHaarClassifierCascade) );
	
	CvHaarClassifierCascade* pCvHaarClassifierCascade = New_CvHaarClassifierCascade(4, 5, 6);

	SettingCvHaarClassifierCascade(pCvHaarClassifierCascade);
}
