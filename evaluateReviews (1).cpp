// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>

// The #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"

using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main(){

// Creates an output stream called report.txt and outputs the stream header to be used later
ofstream fout ("report.txt");
fout << "review" << " " << "score" << " " << "category" << endl;

// Declares all the variables to be used and initializes them when needed
int analyzedReviews = 0;
int truthReviews = 0;
int deceptiveReviews = 0;
int uncatReviews = 0;
double highReview = 0;
double lowReview = 0;
int highestReview = 0;
int lowestReview = 0;
string newReview;
double sum; 
vector <string> review;
vector <string> keywords;
vector <double> weights;

// Opens a file input stream and reads in the keywordWeights file and displays an error message if the file cannot be opened
ifstream fin ("keywordWeights.txt");
if ( !fin.is_open()) {
    cout << "Error: keywordWeights.txt could not be opened."; 
    return 1;
}

// Calls the readKeywordWeights function to input the data into the two separate vector variables
readKeywordWeights (fin, keywords, weights);

// Creates a for loop to iterate through at most 100 reviews, and opens up a file stream for every new review being read in. Also clears the review vector at the beginning of each loop for new words to be read in
for(int i = 0; i < 100; ++i ) {
    newReview = makeReviewFilename(i);
    ifstream fin2 (newReview);
    review.clear();

// Creates an outer if loop that will continuously run as long as a file stream was able to be opened
    if (fin2.is_open()) {

// Calls the readReview function to read in the given review, and calculates the total sum of the given review
        readReview (fin2, review);

        sum = reviewScore (review, keywords, weights);

// Calculates the total number of truthful reviews and outputs to the summary file if it's truthful
        if (sum > SCORE_LIMIT_TRUTHFUL) {
            fout << i << " " << sum << " " << "truthful" << endl;
            ++truthReviews;
        }
// Calculates the number of deceptive reviews and outputs a line to the summary file if it's deceptive
        if (sum < SCORE_LIMIT_DECEPTIVE) {
            fout << i << " " << sum << " " << "deceptive" << endl;
            ++deceptiveReviews;
        }
// Calculates the number of uncategorized reviews and outputs a line to the summary line if undeceptive
        if (sum < SCORE_LIMIT_TRUTHFUL && sum > SCORE_LIMIT_DECEPTIVE) {
            fout << i << " " << sum << " " << "uncategorized" << endl;
        ++uncatReviews;
        }
// Accounts for the special cases when sum is equal to 3.0 or -3.0 and still considers these to be uncategorized
        if (sum == SCORE_LIMIT_DECEPTIVE) {
            fout << i << " " << sum << " " << "uncategorized" << endl;
        ++uncatReviews;
        } else if (sum == SCORE_LIMIT_TRUTHFUL) {
            fout << i << " " << sum << " " << "uncategorized" << endl;
        ++uncatReviews; 
        }
// Calculates the lowest review and returns the index using the previously declared variable
        if (sum < lowReview) {
            lowReview = sum;
            lowestReview = i;
        }
// Calculates the highest review and returns the index using the previously declared variable
        if (sum > highReview) {
            highReview = sum;
            highestReview = i;
        }
// Increments the total number of analyzed reviews everytime the loop is complete
    ++analyzedReviews;
    }
}
// Outputs a blank line 
fout << " " << endl;

// Outputs the total number of reviews
fout << "Number of reviews: " << analyzedReviews << endl;

// Outputs the total number of trutful reviews
fout << "Number of truthful Reviews: " << truthReviews << endl;

// Outputs the total number of deceptive reviews
fout << "Number of deceptive Reviews: " << deceptiveReviews << endl;

// Outputs the total number of uncategorized reviews
fout << "Number of uncategorized reviews: " << uncatReviews << endl;

// Outputs a blank line
fout << " " << endl;

// Outputs the index of the review with the highest score
fout << "Review with highest score: " << highestReview << endl;

// Outputs the index of the review with the lowest score
fout << "Review with lowest score: " << lowestReview;
} 


