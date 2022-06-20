/*
Task: H5
Family Name: Mannan
Given Name: Nasif
Matriculation number: 3055949
Uni-Email: nasif.mannan@stud.uni-due.de
Course of Studies: ISE CSE
*/
#include<bits/stdc++.h>
using namespace std;


class Article{
	string model;
	double netprice, taxRate;
public:
	Article(string modelval, double netpriceval, double taxRateval = 19.00){
		model = modelval;
		netprice = netpriceval;
		taxRate = taxRateval;
	}
	virtual ~Article(){
		cout<<"~Article() ";
		cout<<model<<endl;
	}
	void set_model(string modelval){
		model = modelval;
		return;
	}
	void set_netPrice(double netpriceval){
		netprice = netpriceval;
		return;
	}
	string get_model(){
		return model;
	}
	double get_netPrice(){
		return netprice;
	}
	double get_grossPrice(){
		return netprice * (100 + taxRate)/100.0;
	}
	virtual void print() = 0;
};


class Accessory: public Article{
	bool original;
public:
	Accessory(string article_name, double net_price, bool original_val = true):Article(article_name, net_price){
		original = original_val;
	}
	virtual ~Accessory(){
		cout<<"~Accessory() ";
	}
	virtual void print(){
		cout<<get_model();
		if(original)
			cout<<" (original accessory)";
		cout<<endl;
		return;
	}
};

enum class OperatingSystem{unknown, android, iOS, macOS, Linux, proprietary, Unix, windows};

ostream& operator<<(std::ostream& out, OperatingSystem& OS)
{
    switch(OS)
    {
        case OperatingSystem::unknown:     out<<"unknown OS"; break;
        case OperatingSystem::android:     out<<"Android OS"; break;
        case OperatingSystem::iOS:         out<<"iOS"; break;
        case OperatingSystem::macOS:       out<<"MacOS"; break;
        case OperatingSystem::Linux:       out<<"Linux OS"; break;
        case OperatingSystem::proprietary: out<<"proprietary OS"; break;
        case OperatingSystem::Unix:        out<<"Unix OS"; break;
        case OperatingSystem::windows:     out<<"MS Windows OS"; break;
    }
}


class Device: public Article{
	int main_memory;
	OperatingSystem os;
public:
	Device(string article_name, double netprice, int mainMemory, OperatingSystem operating_system = OperatingSystem::unknown):Article(article_name, netprice){
		main_memory = mainMemory;
		os = operating_system;
	}
	virtual ~Device(){
		cout<<"~Device() ";
	}
	OperatingSystem get_os(){
		return os;
	}
	virtual void print(){
		cout<<get_model()<<", RAM "<<main_memory<<"GB, "<<os;
		return;
	}
};


class Notebook: public Device{
	string drive;
	bool convertible;
public:
	Notebook(string article_name, double netprice, int main_memory, string driveVal, OperatingSystem os = OperatingSystem::Linux, bool convertible = false):
		Device(article_name, netprice, main_memory, os)
	{
		drive = driveVal;
	}
	virtual ~Notebook(){
		cout<<"~Notebook() ";
	}
	bool is_a_convertible(){
		return convertible;
	}
	virtual void print(){
		Device::print();
		if(convertible)
			cout<<" (convertible) ";
		cout<<drive<<endl;
		return;
	}
};


class Phone: public Device{
public:
	Phone(string article_name, double netprice, int main_memory = 4, OperatingSystem os = OperatingSystem::android):Device(article_name, netprice, main_memory, os){}
	virtual ~Phone(){
		cout<<"~Phone() ";
	}
	virtual void print(){
		Device::print();
		cout<<" phone"<<endl;
		return;
	}
};

class InCart{
	Article* article;
	int amount;
	InCart* next;
public:
	InCart(Article* article_val, int amount_val = 0, InCart *nextVal = NULL){
		article = article_val;
		amount = amount_val;
		next = nextVal;
	}
	virtual ~InCart(){
		cout<<"~InCart() "<<amount<<" ";
		delete article;
	}
	InCart* get_next(){
		return next;
	}
	virtual void print(){cout<<amount<<" ";
		cout<<amount<<" ";
		article->print();
		double grossAmountPerItem = article->get_grossPrice();
		cout<<fixed<<setprecision(2);
		cout<<setw(55)<<right<<grossAmountPerItem<<"  EUR\t\t"<<setw(10)<<right<<grossAmountPerItem*amount<<"  EUR"<<endl;
		return;
	}
};

class ShoppingCart{
	InCart* articles;
	double minFressShipping;
	double sumNetPrice;
	double sumGrossPrice;
public:
	ShoppingCart(){
		articles = NULL;
		minFressShipping = 1000;
		sumGrossPrice = 0;
		sumNetPrice = 0;
	}
	~ShoppingCart(){
		cout<<"~ShoppingCart()"<<endl;
		InCart *nextElem = NULL, *currElem = articles;
		while(currElem){
			cout<<"delete article: ";
			nextElem = currElem->get_next();
			delete currElem;
			currElem = nextElem;
		}
	}
	void set_minFreeShipping(double minFressShippingVal){
		minFressShipping = minFressShippingVal;
		return;
	}
	void add_article(double amount, Article *article){
		articles = new InCart(article, amount, articles);
		sumNetPrice += amount * article->get_netPrice();
		sumGrossPrice += amount *  article->get_grossPrice();
		return;
	}
	virtual void print(){
		cout<<endl<<endl<<endl;
		cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		cout<<endl;
		cout<<"+\t\t\t      P R O T O - T E C - S H O P  \t\t\t\t+"<<endl;
		cout<<"+\t\t\t    Y O U R   S H O P P I N G C A R T    \t\t\t+"<<endl;
		cout<<endl;
		cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
		InCart* temp = articles;
		while(temp){
			// need to update
			cout<<endl;
			temp->print();
			temp = temp->get_next();
		}
		cout<<fixed<<setprecision(2);
		cout<<setw(90)<<right<<"-------------------"<<endl;
		cout<<endl;
		cout<<setw(65)<<right<<"sum net price:\t"<<setw(11)<<right<<sumNetPrice<<" EUR"<<endl;
		cout<<endl;
		cout<<setw(65)<<right<<"tax:\t"<<setw(11)<<right<<sumGrossPrice-sumNetPrice<<" EUR"<<endl;
		cout<<endl;
		cout<<setw(65)<<right<<"sum net price:\t"<<setw(11)<<right<<sumGrossPrice<<" EUR"<<endl;
		cout<<endl;
		cout<<setw(90)<<right<<"-------------------"<<endl;
		cout<<endl;
		double shippingCharges = (sumGrossPrice > minFressShipping) ? 0.00 : 5.90;
		cout<<setw(65)<<right<<"shipping:\t"<<setw(11)<<right<<shippingCharges<<" EUR"<<endl;
		cout<<endl;
		cout<<setw(90)<<right<<"-------------------"<<endl;
		cout<<endl;
		cout<<setw(65)<<right<<"total:\t"<<setw(11)<<right<<sumGrossPrice+shippingCharges<<" EUR"<<endl;
		cout<<endl;
		cout<<setw(90)<<right<<"-------------------"<<endl;
		cout<<setw(90)<<right<<"-------------------"<<endl;
		return;
	}
};
/*
*/
int main(){
	ShoppingCart shoppingCart;
	shoppingCart.set_minFreeShipping(500);
	Article* powerbank = new Accessory("YOOLOX 10k Wireless Powerbank Qi", 31.08, false);
	shoppingCart.add_article(3, powerbank);

	shoppingCart.print();
	Article* phone1 = new Phone("Samsung Galaxy S10+ SMG975F/DS Dual SIM", 661.67, 8);
	shoppingCart.add_article(1, phone1);
	Article* phone2 = new Phone("Apple iPhone 11 Pro 256GB", 1097.47, 4, OperatingSystem::iOS);
	shoppingCart.add_article(2, phone2);
	Article* notebook = new Notebook("ASUS ROG Strix Scar III G731", 1586.55, 16, "512GB SSD + 1TB SSHD", OperatingSystem::windows);
	shoppingCart.add_article(1, notebook);
	shoppingCart.print();

	return 0;
}
