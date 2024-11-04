#include<iostream>
#include<vector>
#include<string>
using namespace std;
#define pb push_back
class Vehicle{
public:
	string namePlate;
	int ownerID;
	Vehicle();
};
class Car : public Vehicle{
	Car(int _ownerID){
		namePlate = 'A0000';
		ownerID = _ownerID;
	}
};
class Bike : public Vehicle{
	Bike(int _ownerID){
		namePlate = 'A0000';
		ownerID = _ownerID;
	}
};
class User{
	int uid;
	vector< Vehicle > vehicles;
	User(){

	}
	void addVehicle(Vehicle v){
		vehicles.pb(v);
	}
	Vehicle getVehicle(string _namePlate){}
};
class ParkingLot{
	vector< Vehicle > parking;
	int lotSizeCars;
	int lotSizeBikes;
	int parkingRate;
	int parkVehicle(Vehicle v){
		// returns the parking lot id;
	}
	int getVehicleLocation(string name){

	}
	int unparkVehicle(int parkingNumber, int uid){
		// returns the amount to be paid.
	}
	bool receivePayment(){
		// returns true if payment done, false otherwise.
	}
	int getRevenue(){
		// return the parking Lot revenue.
	}
}
