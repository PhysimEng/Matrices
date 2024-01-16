#include <iostream>
#include <vector>
#include <time.h>


template <typename T> 
class Matrix{
protected: 
std::vector<T> V;	
int row;  
int col;

public: 
Matrix(int row, int col) {
	this->setRow(row); 
	this->setCol(col);  
    this->createMatrixAsARandomVector();
}

void setMatrix(std::vector<T> in){
	//this->V = in;
	for(int i=0; i<in.size();i++) this->V.push_back(in.at(i));  

}  

void  setRow(int row){
	this->row = row;
}

int getRow(){
	return this->row;
}  
void setCol(int col){
	this->col = col;
}

int getCol(){
	return this->col; 
}
std::vector<T> getV(){
	return this->V; 
}
void printMatrix(){
	int index=0;
	for(T num:this->V){
		index++;
		std::cout<<num<<" ";
		if(index % this->col == 0) std::cout<<std::endl;
} 
}

protected: 
T getRandomValue() {
    T lowerBound = 0;
    T upperBound = 1000;
	double factor = 0.0000000001;
    int randomInt = rand(); 

    if (std::is_same<T, int>::value) {
        return randomInt/10000000;
    } else if (std::is_same<T, double>::value) {
        return factor*(lowerBound + (upperBound - lowerBound) * static_cast<double>(randomInt)) ;
    } else {
		std::cout<<"Sorry not Suported bye"<<std::endl;
		exit(1);
        return T{};
    }
} 
void createMatrixAsARandomVector(){

 
    srand(time(NULL));

    for(int i=0; i<this->row*this->col; i++){
    T randomNumber = this->getRandomValue();
    this->V.push_back(randomNumber);
    }
} 


}; 

template <typename T> 
class MatrixMult{ 
const long max_rand = 1000000L;
protected: 
Matrix<T> A;
Matrix<T> B;
Matrix<T> BorganizedB; 
Matrix<T> C;

public: 
MatrixMult(Matrix<T> Ain, Matrix<T> Bin) : A(Ain), B(Bin), BorganizedB(B.getRow(), B.getCol()), C(A.getRow(),B.getCol()){
    if (!this->checkMult()) {
        std::cout << "Sorry not possible to Compute. Try Again" << std::endl;
        exit(1);
    }
}

Matrix<T> getA(){
	return this->A;
} 
Matrix<T> getB(){
	return this->B;
}
Matrix<T> getC(){
	return this->C;
} 
std::vector<T> reorganizeVectorB() {
    int n = this->B.getV().size();
    std::vector<T> BOrganized;
    
    int set = 0;
    int index =0;   
    
    for (int i=0; i<n; i++) { 
    	BOrganized.push_back(this->B.getV()[index]);
    	index+=this->B.getCol();
    	if(index>=n){
    	set++;
    	index=set;   
    	}
    }    
    return BOrganized;
}
	
std::vector<T> duplicateVectorB(){
	this->BorganizedB.setMatrix(this->reorganizeVectorB());
	std::vector<T> duplicateB;
	int index=0;
	for(int i=0; i<(this->B.getV().size()*this->A.getRow()); i++){
		duplicateB.push_back(this->BorganizedB.getV()[index]);
		if(index == this->B.getV().size()-1){
			index = -1;
		}
		index++;
		   
	}
	return duplicateB; 		
}
std::vector<T> duplicateVectorA(){
	std::vector<T> duplicateA;

	int index =0;
	int count=0;
	for(int i=0;i<(this->B.getCol()*this->B.getRow()*this->A.getRow()); ++i){
		if(index%this->B.getRow() == 0 && index !=0){
			index -=(this->B.getRow());
			count++;
			if((count%this->B.getCol()) ==0 && count !=0){
				index = (count/(this->B.getCol()))*(this->B.getRow());
			}   
		}
		duplicateA.push_back(this->A.getV()[index]);
		index++;	   
	}		
	
	return duplicateA;
}
void  matrixMultiply(){
	std::vector<T> DuplyA = this->duplicateVectorA();
	std::vector<T> DuplyB = this->duplicateVectorB();
	std::vector<T> products;
	
	T element =0;
	std::vector<T> result;
	for(int i=0; i<DuplyA.size(); i++){
		products.push_back(DuplyA[i]*DuplyB[i]);
		if(i%2==0 && i!=0){
		result.push_back(products.at(i-1)+products.at(i)); 
		}  
		 
	}
	this->C.setMatrix(result);	
}
 
protected: bool checkMult(){
	return A.getCol() == B.getRow();
} 
     
};   
int main() { 
	Matrix<int> A(3,2);
	Matrix<int> B(2,4);
	MatrixMult<int> matrixMultiplierA(A,B);
	matrixMultiplierA.getA().printMatrix();
	std::cout<<"\n";
	matrixMultiplierA.getB().printMatrix();
	std::cout<<"\n";
	matrixMultiplierA.matrixMultiply();
	std::cout<<"\n";  
	matrixMultiplierA.getC().printMatrix();  
	/*MatrixMult<int> matrixMultiplierB(3,3,3,2);
    matrixMultiplierB.getA().printMatrix(); 
	matrixMultiplierB.getB().printMatrix();	*/	    
    return 0;
}

