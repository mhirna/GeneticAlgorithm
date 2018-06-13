#include <algorithm>
#include <thread>
#include "Populaton.h"

using namespace std;

bool sortFunc(Chromosome first , Chromosome second){ return first.fitness > second.fitness;}

//void Populaton::calc_fit(size_t start, size_t end) {
//    for (int i = start; i <= end; i++)
//    {
//        population_set[i].calc_fitnes();
//    }
//}
//
//void Populaton::calc_ratio(size_t start, size_t end) {
//    for (int i = start; i <= end; i++)
//    {
//        population_set[i].calc_ratio(best_chromosome);
//    }
//}

void Populaton::runAlgorithm() {
        probabilry_crossover();
        probabilry_mutate();
        refresh_nofit();
}

void Populaton::init() {

    population_set = generate_population(population_size);

    calc_fit_ratio();
}

std::vector<Chromosome> Populaton::generate_population(size_t population_size) {
    vector<Chromosome> population;

    for (int i = 0; i < population_size; ++i) {
        population.push_back(Chromosome(chromosome_size, fitnes_func));
    }

    return population;
}
//
//void Populaton::parallel_calc_fitnes() {
//    vector<thread> threads;
//    size_t start = 0;
//    size_t end = 0;
//
//    for (int i = 1; i <= theard_num; i++)
//    {
//        if(i == theard_num)
//        {
//            end = population_size;
//        }
//        else
//        {
//            end += population_size/theard_num ;
//        }
//        threads.push_back(thread(&Populaton::calc_fit,this, start, end));
//        start = end;
//    }
//    for (int i = 0; i < theard_num; i++)
//    {
//        threads[i].join();
//    }
//
//}
//
//void Populaton::parallel_calc_ratio() {
//    vector<thread> threads;
//    size_t start = 0;
//    size_t end = 0;
//
//    for (int i = 1; i <= theard_num; i++)
//    {
//        if(i == theard_num)
//        {
//            end = population_size;
//        }
//        else
//        {
//            end += population_size/theard_num ;
//        }
//        threads.push_back(thread(&Populaton::calc_ratio,this, start, end));
//        start = end;
//    }
//    for (int i = 0; i < theard_num; i++)
//    {
//        threads[i].join();
//    }
//}

void Populaton::calculateProbability() {
    
    double fitnes_sum = 0;

    for (Chromosome chromosome : population_set) {
        fitnes_sum += chromosome.fitness;
}

    for (int i = 0; i < population_size; ++i) {
        population_set[i].probability = ((population_set[i].fitness/fitnes_sum) * (1 - population_set[i].ratio));
    }
}


int findCeilVec(vector<int> arr, int r, int l, int h){
    int mid;
    while (l < h)
    {
        mid = l + ((h - l) >> 1);  // Same as mid = (l+h)/2
        (r > arr.at(mid)) ? (l = mid + 1) : (h = mid);
    }
    return (arr.at(l) >= r) ? l : -1;
}

int myRandVec(vector<int> arr, vector<double> freq, int n){
    vector<int> prefix;
    int j;

    prefix.push_back(arr.at(0));

    for (j = 1; j < n; ++j)
        prefix.push_back(prefix.at(j - 1) + arr.at(j));


    int r = (rand() % prefix.at(n - 1)) + 1;

    int indexc = findCeilVec(prefix, r, 0, n - 1);
    return arr.at(indexc);

}

void Populaton::probabilry_crossover() {
//    srand ( (unsigned) time(NULL) );
    calculateProbability();

    vector<double> vector_probabilities(population_size);

    for (int i = 0; i < population_size; ++i) {
        vector_probabilities[i] = population_set[i].probability;
        }

    vector<int> index_vector = {0,1,2,3,4,5,6,7,8,9};

    vector<int> ind_ddd;
    int random=0;
    int new_random=0;
    for (int j = 0; j < population_size*cross_prob; ++j) {
        while(random == new_random){
            new_random = myRandVec(index_vector, vector_probabilities, population_size);
            if(find(ind_ddd.begin(), ind_ddd.end(), new_random) != ind_ddd.end()){
                random = new_random;
                continue;
            }
        }
        random = new_random;
        ind_ddd.push_back(random);
    }

    vector<Chromosome> new_pop;
    Chromosome chromosome1;
    Chromosome chromosome2;
    for (int k = 0; k < ind_ddd.size(); ++k) {
        if(k%2 != 0){
            continue;
        }
        chromosome1 = population_set[ind_ddd[k]];
        chromosome2 = population_set[ind_ddd[k+1]];
        vector<Chromosome> fff = chromosome1.crossover(&chromosome2);
        for (int i = 0; i < 2; ++i) {
            new_pop.push_back(fff[i]);
        }
    }

    for (int j = 0; j < population_size; ++j) {
        if(find(ind_ddd.begin(), ind_ddd.end(), j) == ind_ddd.end()){
            new_pop.push_back(population_set[j]);
        }

    }
    population_set = new_pop;
    calc_fit_ratio();


}

void Populaton::probabilry_mutate() {
    for (int i = 0; i < population_size; ++i) {
        double random_num = ((double) rand() / (RAND_MAX)) ;
        if(random_num < prob_mut){
            population_set[i].mutate();
        }
    }
    calc_fit_ratio();
}

void Populaton::refresh_nofit() {
    int lethal_num = static_cast<int>(population_size * lethal);


    sort(population_set.begin(), population_set.end(), sortFunc);

    best_chromosome = population_set[0];

    vector<Chromosome> sub_population = generate_population(lethal_num);

    for (int i = 0; i < lethal_num; ++i) {
        population_set.pop_back();
    }

    for (int j = 0; j < lethal_num; ++j) {
        sub_population[j].calc_fitnes();
        sub_population[j].calc_ratio(best_chromosome);
        population_set.push_back(sub_population[j]);
    }
    calc_fit_ratio();
}

void Populaton::calc_fit_ratio() {
    for (int i = 0; i < population_size; i++)
    {
        population_set[i].calc_fitnes();
    }

    sort(population_set.begin(), population_set.end(), sortFunc);
    best_chromosome = population_set[0];
    worst_chromosome = population_set[1];
    for (int i = 0; i < population_size; i++)
    {
        population_set[i].calc_ratio(best_chromosome);
    }
}
