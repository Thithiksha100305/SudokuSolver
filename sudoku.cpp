#include<iostream>
#include<vector>
using namespace std;
//representation of sudoko board
//2d array
void printSudoku(int arr[9][9]){
    cout<<"-------------------------"<<endl;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"-------------------------"<<endl;
    
}

bool CanPlace(int arr[9][9],int row,int col,int n){
    if(arr[row][col] != 0){
        return false;
    }
    bool status=true;
    int gridx=(col/3) * 3;
    int gridy= (row/3) * 3;
    for(int i=0;i<9;i++){
        if(arr[row][i]==n){
            status=false;
            break;
        }
        if(arr[i][col]==n){
            status=false;
            break;
        }
        if(arr[gridy+i/3][gridx +i %3]==n){
            status=false;
            break;
        }
        
    }
    return status;

}
void nextEmpty(int arr[9][9],int row,int col,int &nRow,int &nCol){
    int index=9 * 9+ 1; 
    for(int i=row*9+col+1 ;i< 9 * 9 ;i++){
        if(arr[i/9][i%9]==0){
            index=i;
            break;
        }
    }
    nRow=index / 9;
    nCol=index % 9;
}
void copyArray(int arr[9][9],int arrCopy[9][9]){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            arrCopy[i][j]=arr[i][j];
        }
    }
}

vector<int> FindPlacebles(int arr[9][9],int r,int c){
    vector<int>cps ={};
    for(int i=1;i<=9;i++){
        if(CanPlace(arr,r,c,i)){
            cps.push_back(i);
        }
    }
    return cps;

}


bool SolveSudoku(int arr[9][9],int r,int c){
    //system("cls");
    //printSudoku(arr);
    if(r>8){
        return true;
    }
    if(arr[r][c] !=0){
        int nextRow,nextCol;
        nextEmpty(arr,r,c,nextRow,nextCol);
        return SolveSudoku(arr,nextRow,nextCol);
    }
    vector<int> placebles=FindPlacebles(arr,r,c);
    if(placebles.size()==0){
        return false;
    };
    bool status =false;
    for(int i=0;i<placebles.size();i++){
        int n=placebles[i];
        int arrCpy[9][9];
        copyArray(arr,arrCpy);
        arrCpy[r][c]=n;
        int nextCol=c,nextRow=r;
        nextEmpty(arr,r,c,nextRow,nextCol);
        if(SolveSudoku(arrCpy,nextRow,nextCol)){
            copyArray(arrCpy,arr);
            status=true;
            break;
        }
    }
    return status;
}

int main(int argc, char** argv){
    int board[9][9]={
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };
    //printSudoku(board);
    //SolveSudoku(board,0,0);
    //printSudoku(board);
    if (SolveSudoku(board, 0, 0)) cout << "successfully solved board!" << std::endl;
	printSudoku(board);

    return 0;
}