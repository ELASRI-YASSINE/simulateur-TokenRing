#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure représentant une station
typedef struct Station {
    int id;                     // Identifiant de la station
    bool has_token;             // Indique si la station a le jeton
    struct Station* next;       // Pointeur vers la station suivante
    int data_to_send[10];       // Données à transmettre
    int data_count;             // Nombre de données à transmettre
} Station;

// Structure représentant le réseau Token Ring
typedef struct {
    Station* stations;          // Tableau des stations
    int num_stations;           // Nombre de stations
    Station* current_token_holder; // Station actuellement en possession du jeton
} TokenRingNetwork;

// Fonction pour créer une station
Station* create_station(int id) {
    Station* station = (Station*)malloc(sizeof(Station));
    station->id = id;
    station->has_token = false;
    station->next = NULL;
    station->data_count = 0;
    return station;
}

// Fonction pour initialiser le réseau Token Ring
TokenRingNetwork* create_token_ring_network(int num_stations) {
    TokenRingNetwork* network = (TokenRingNetwork*)malloc(sizeof(TokenRingNetwork));
    network->num_stations = num_stations;
    network->stations = (Station*)malloc(num_stations * sizeof(Station));

    for (int i = 0; i < num_stations; i++) {
        network->stations[i] = *create_station(i);
        if (i > 0) {
            network->stations[i - 1].next = &network->stations[i];
        }
    }
    network->stations[num_stations - 1].next = &network->stations[0]; // Fermer l'anneau

    network->current_token_holder = &network->stations[0];
    network->current_token_holder->has_token = true;

    return network;
}

