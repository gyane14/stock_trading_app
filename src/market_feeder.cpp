#include <zmq.hpp>
#include <iostream>
#include <thread>
#include <random>

void generate_market_data( zmq::socket_t &publisher ) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distributiion<> dis(100.0, 200,0);

	while(true) {
	
		double price = dis(gen);
		std::string message = "AAPL " + std::to_string(price);

		zmq::message_t zmq_msg(message.size());
		memcpy(zmq_msg.data(), message.c_str(), message.size());
		publisher.send(zmq_msg, zmq::send_flags::none);

		std::this_thread::sleep_for(std::chrono::miliseconds(500));
	}

}

int main() {

	zmq::context_t contex(1);
	zmq::socket_t publisher(context, ZMQ_PUB);
	publisher.bind("tcp://*:5556");

	std::cout << "Market Data Feefer started...\n";
	generate_market_data(publisher);


	return 0;
}
