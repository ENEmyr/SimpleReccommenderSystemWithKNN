#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main(){

    /* Assignment */
    const int featureNum = 2;
    int dataset[10][featureNum+1] = { 
        // form : {feature1, feature2, class}
        {7, 2, 2},
        {8, 10, 1},
        {4, 3, 2},
        {10, 5, 2},
        {9, 7, 2},
        {1, 10, 2},
        {6, 8, 2},
        {5, 9, 2},
        {2, 6, 1},
        {1, 9, 1}
    };
    float distance[3][2]= { 
        // form : {distance, class}
        {0, 0},
        {0, 0},
        {0, 0}
    };
    int newdata[2][featureNum+1] = { 
        // form : {feature1, feature2, class}
        {2, 8, 0}, // class must be 1
        {7, 10, 0}, // class must be 2
    };
    int newdata_size = sizeof(newdata) / sizeof(*newdata);
    int dataset_size = sizeof(dataset) / sizeof(*dataset);
    int distance_size = sizeof(distance) / sizeof(*distance);

    /* K-Nearest Algorithm */
    for(int i = 0; i < newdata_size ; i++){
        for(int j = 0; j < dataset_size ; j++){
            float euclideanDis = 0;
            for(int l = 0 ; l < featureNum ; l++) euclideanDis += pow(newdata[i][l] - dataset[j][l], 2);
            euclideanDis = sqrt(euclideanDis);
            cout << "Distance between newdata[" << i << "] and dataset[" << j << "] = " << fixed << setprecision(5) << euclideanDis << endl;
            if (j < 3) {
                distance[j][0] = euclideanDis;
                distance[j][1] = dataset[j][2];
                continue;
            }
            if(euclideanDis - distance[0][0] <= 0 || euclideanDis - distance[1][0] <=0 || euclideanDis - distance[1][0] <= 0 || euclideanDis - distance[2][0] <= 0){
                if(distance[0][0] > distance[1][0]){
                    if(distance[0][0] > distance[2][0]){
                        distance[0][0] = euclideanDis;
                        distance[0][1] = dataset[j][2];
                    }else{
                        distance[2][0] = euclideanDis;
                        distance[2][1] = dataset[j][2];
                    }
                }else if(distance[1][0] > distance[0][0]){
                    if(distance[1][0] > distance[2][0]){
                        distance[1][0] = euclideanDis;
                        distance[1][1] = dataset[j][2];
                    }else{
                        distance[2][0] = euclideanDis;
                        distance[2][1] = dataset[j][2];
                    }
                }else{
                    if(distance[0][0] > distance[2][0]){
                        distance[0][0] = euclideanDis;
                        distance[0][1] = dataset[j][2];
                    }else{
                        distance[2][0] = euclideanDis;
                        distance[2][1] = dataset[j][2];
                    }
                }
            }
        }
        //Classified newdata from 3-nearest neighbours
        if(distance[0][1] == distance[1][1]) newdata[i][2] = distance[0][1];
        else if(distance[0][1] == distance[2][1]) newdata[i][2] = distance[0][1];
        else newdata[i][2] = distance[1][1];
        //Printing result
        cout << "\nList of minimum distance and class \n===================================\n";
        for(int l = 0; l < distance_size ; l++)
            cout << "Distance = " << fixed << setprecision(5) << distance[l][0] << setw(15) << " , Class = "<< setprecision(0) << distance[l][1] << endl;
        cout << "===================================\nConclusion\nClass of newdata[" << i << "] = " << newdata[i][2];
        cout << "\n\n************************************************************\n\n";
    }
    return 0;
}
