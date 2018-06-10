/*
 * main.cpp
 *
 *  Created on: Jun 4, 2018
 *      Author: Ruikun
 */


#include <iostream>
#include <vector>
#include <iterator>

namespace {

using namespace std;

int main() {
    vector<int> v{4,2,3,3,1,2,3,4,5,4,2,3};
    cout << "original vector: " << flush;
    for (auto item : v) { cout << item << "," << flush; }
    cout << endl;

    //sort the vector
    sort(v.begin(), v.end());

    cout << "sorted vector: " << flush;
    for (auto item : v) { cout << item << "," << flush; }
    cout << endl;

    auto resultOfUnique = std::unique( v.begin(), v.end() );
    cout << "position of the resultOfUnique: " << std::distance(v.begin(), resultOfUnique) << endl;

    cout << "print elements from the beginning to the resultOfUnique:" << endl;
    for (auto it = v.begin(); it != resultOfUnique; ++it) { cout << *it << "," << flush;}
    cout << endl;

    cout << "print elements from the resultOfUnique to the end of the sorted vector: " << endl;
    for (auto it = resultOfUnique; it != v.end(); ++it) { cout << *it << "," << flush;}
    cout << endl;

    cout << "distance between end and begin: " << std::distance(v.begin(), v.end()) << endl;

    cout << "erase the elements after the resultOfUnique" << endl;
    auto resultOfErase = v.erase(resultOfUnique, v.end());
    cout << "distance between resultOfErase end and begin: " << std::distance(v.begin(), resultOfErase) << endl;
    cout << "print the final result: " << endl;

    for (auto& item : v) { cout << item << "," << flush;}
    cout << endl;

    return 0;

}

} // end of namespace
