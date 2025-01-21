#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure repr�sentant une station
typedef struct Station {
    int id;                     // Identifiant de la station
    bool has_token;             // Indique si la station a le jeton
    struct Station* next;       // Pointeur vers la station suivante
    int data_to_send[10];       // Donn�es � transmettre
    int data_count;             // Nombre de donn�es � transmettre
} Station;

// Structure repr�sentant le r�seau Token Ring
typedef struct {
    Station* stations;          // Tableau des stations
    int num_stations;           // Nombre de stations
    Station* current_token_holder; // Station actuellement en possession du jeton
} TokenRingNetwork;

// Fonction pour cr�er une station
Station* create_station(int id) {
    Station* station = (Station*)malloc(sizeof(Station));
    station->id = id;
    station->has_token = false;
    station->next = NULL;
    station->data_count = 0;
    return station;
}

// Fonction pour initialiser le r�seau Token Ring
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

// Fonction pour simuler une �tape du r�seau
void simulate_step(TokenRingNetwork* network) {
    Station* current_station = network->current_token_holder;

    if (current_station->data_count > 0) {
        printf("Station %d transmet des donn�es: %d\n", current_station->id, current_station->data_to_send[0]);
        for (int i = 0; i < current_station->data_count - 1; i++) {
            current_station->data_to_send[i] = current_station->data_to_send[i + 1];
        }
        current_station->data_count--;
    }

    current_station->has_token = false;
    current_station->next->has_token = true;
    network->current_token_holder = current_station->next;
    printf("Station %d passe le jeton � Station %d\n", current_station->id, current_station->next->id);
}

// Fonction pour ajouter des donn�es � une station
void add_data_to_station(TokenRingNetwork* network, int station_id, int data) {
    if (station_id >= 0 && station_id < network->num_stations) {
        Station* station = &network->stations[station_id];
        if (station->data_count < 10) {
            station->data_to_send[station->data_count] = data;
            station->data_count++;
            printf("Donn�e %d ajout�e � la Station %d\n", data, station_id);
        } else {
            printf("La Station %d a trop de donn�es en attente\n", station_id);
        }
    } else {
        printf("Station %d invalide\n", station_id);
    }
}
int main() {
    int num_stations = 5; // Nombre de stations dans le r�seau
    TokenRingNetwork* network = create_token_ring_network(num_stations);

    // Ajouter des donn�es aux stations
    add_data_to_station(network, 0, 100);
    add_data_to_station(network, 1, 200);
    add_data_to_station(network, 3, 300);

    // Simuler les �tapes du r�seau
    for (int i = 0; i < 10; i++) {
        printf("\n�tape %d:\n", i + 1);
        simulate_step(network);
    }

    // Lib�rer la m�moire
    free(network->stations);
    free(network);

����return�0;
}
