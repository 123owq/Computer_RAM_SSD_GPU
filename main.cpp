#include <iostream>

class computerInterface { // computer 인터페이스 
public:
	virtual int getValue() = 0;
	virtual std::string getName() = 0;
};

class computer: public computerInterface { // computer 구현
private:
	int value = 500000;
	std::string Name = "Computer";
public:
	int getValue() override {
		return this->value;
	}
	std::string getName() {
		return Name;
	}
};

class computerDecorator : public computerInterface { // 데코레이터 추상클래스
protected:
	std::shared_ptr<computerInterface> decorator; // shared_ptr로 객체 참조갯수 관리 
public:
	explicit computerDecorator(std::shared_ptr<computerInterface> decorator): decorator(std::move(decorator)) {}
	int getValue() override {//explicit으로 이 생성자로만 생성되게함. computerInterface 객체로 decorator 초기화해서 나중에 데코레이트 가능하게함
		return decorator->getValue(); // 기존객체의 getValue() getName() 리턴
	}
	std::string getName() override {
		return decorator->getName();
	}

};

class RAM : public computerDecorator {
public:
	explicit RAM(std::shared_ptr<computerInterface> decorator) : computerDecorator(std::move(decorator)) {}
	// computerInterface 객체 들어오면 computerDecorator 생성자 사용해서 decorator 초기화 
	int getValue() override { // override 해서 부품값 더하고, 이름 합침. 
		return decorator->getValue() + value;
	}
	std::string getName() override {
		return Name+decorator->getName();
	}
private:
	int value = 50000;
	std::string Name = "RAM";
};

class SSD : public computerDecorator {
public:
	explicit SSD(std::shared_ptr<computerInterface> decorator) : computerDecorator(std::move(decorator)) {}

	int getValue() override {
		return decorator->getValue() + value;
	}
	std::string getName() override {
		return Name+decorator->getName();
	}
private:
	int value = 80000;
	std::string Name = "SSD";
};

class GPU : public computerDecorator {
public:
	explicit GPU(std::shared_ptr<computerInterface> decorator) : computerDecorator(std::move(decorator)) {}

	int getValue() override {
		return decorator->getValue() + value;
	}
	std::string getName() override {
		return Name+decorator->getName();
	}
private:
	int value = 200000;
	std::string Name = "GPU";
};

int main() {
	char addRAM, addSSD, addGPU;
	std::shared_ptr<computerInterface> Computer = std::make_shared<computer>();
	// computerInterface 객체인 Computer 이 computer 객체를 가리키게함
	
	std::cout << "Add RAM ? (y / n) ";
	std::cin >> addRAM; // 질문하고 y 입력되면 
	if (addRAM == 'y') {// RAM 생성자에 Computer 넣고 생긴 객체를 Computer 에 할당 getValue() getName() 값이 변함
		Computer = std::make_shared<RAM>(Computer);
	}
	std::cout << "Add SSD ? (y / n) ";
	std::cin >> addSSD;
	if (addSSD == 'y') {
		Computer = std::make_shared<SSD>(Computer);
	}
	std::cout << " Add GPU ? (y / n) ";
	std::cin >> addGPU;
	if (addGPU == 'y') {
		Computer = std::make_shared<GPU>(Computer);
	}
	// RAMGPUComputer, 750000
	std::cout << Computer->getName() << ", " << Computer->getValue();
	return 0;
}