#include "mainwin.h"
#include "entrydialog.h"
#include <iostream> //for std::cerr logging
#include <sstream>

Mainwin::Mainwin() : store{new Store()} { 

	//GUI SETUP//

	set_default_size(800,600);
	set_title("Exceptional Laptops and Supercomputer Always (ELSA) Store");
	
	//put vertical box container as the window contents for nesting later
	Gtk::Box *vbox = Gtk::manage(new Gtk::VBox); //manage will automatically delete all widgets from the heap if window closes
	add(*vbox);

	//MENU BAR//
	//add a menu bar as top item of the vbox
	Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
	vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
	//alternatively, vbox->add(*menubar)

	//FILE//
	//create file menu item and add to menu bar w/ accelerator to allow Alt+F
	Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
	menubar->append(*menuitem_file);

	//create menu drop down within menu item
	Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
	menuitem_file->set_submenu(*filemenu);

	//quit - append to file menu
	Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
	//watch for when clicked
	menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
	filemenu->append(*menuitem_quit);

	//--------------

	//VIEW//
	//create view menu item and add to menu bar
	Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
	menubar->append(*menuitem_view);

	//create submenus with customer, peripheral, desktop, order menuitems added
	Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
	menuitem_view->set_submenu(*viewmenu);

	//customer - append to view menu
	Gtk::MenuItem *menuitem_view_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
	menuitem_view_customer->signal_activate().connect([this] {this->on_view_customer_click();});
	viewmenu->append(*menuitem_view_customer);

	//peripheral - append to view menu
	Gtk::MenuItem *menuitem_view_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
	menuitem_view_peripheral->signal_activate().connect([this] {this->on_view_peripheral_click();});
	viewmenu->append(*menuitem_view_peripheral);

	//desktop - append to view menu
	Gtk::MenuItem *menuitem_view_desktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
	menuitem_view_desktop->signal_activate().connect([this] {this->on_view_desktop_click();});
	viewmenu->append(*menuitem_view_desktop);

	//order - append to view menu
	Gtk::MenuItem *menuitem_view_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
	menuitem_view_order->signal_activate().connect([this] {this->on_view_order_click();});
	viewmenu->append(*menuitem_view_order);

	//--------------

	//INSERT//
	//create insert menuitem and append to menubar
	Gtk::MenuItem *menuitem_insert = Gtk::manage(new Gtk::MenuItem("_Insert", true));
	menubar->append(*menuitem_insert);

	//create submenu
	Gtk::Menu *insertmenu = Gtk::manage(new Gtk::Menu());
	menuitem_insert->set_submenu(*insertmenu);

	//customer - append to insert menu
	Gtk::MenuItem *menuitem_insert_customer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
	menuitem_insert_customer->signal_activate().connect([this] {this->on_insert_customer_click();});
	insertmenu->append(*menuitem_insert_customer);

	//peripheral - insert menu
	Gtk::MenuItem *menuitem_insert_peripheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
	menuitem_insert_peripheral->signal_activate().connect([this] {this->on_insert_peripheral_click();});
	insertmenu->append(*menuitem_insert_peripheral);

	//desktop - insert menu
	Gtk::MenuItem *menuitem_insert_desktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
	menuitem_insert_desktop->signal_activate().connect([this] {this->on_insert_desktop_click();});
	insertmenu->append(*menuitem_insert_desktop);

	//order - insert menu
	Gtk::MenuItem *menuitem_insert_order = Gtk::manage(new Gtk::MenuItem("_Order", true));
	menuitem_insert_order->signal_activate().connect([this] {this->on_insert_order_click();});
	insertmenu->append(*menuitem_insert_order);

	//--------------	

	//HELP//
	//create help menu item and add to menubar
	Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
	menubar->append(*menuitem_help);

	//create submenu
	Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
	menuitem_help->set_submenu(*helpmenu);

	//about - help menu
	Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
	menuitem_about->signal_activate().connect([this] {this->on_about_click();});
	helpmenu->append(*menuitem_about);

	//--------------

	//DISPLAY//

	data = Gtk::manage(new Gtk::Label());
	data->set_hexpand(true);
	data->set_vexpand(true);
	vbox->pack_start(*data, Gtk::PACK_SHRINK, 0);
	
	//status bar
	msg = Gtk::manage(new Gtk::Label());
	msg->set_hexpand(true);
	vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);

	//make the box and everything in it visible
	vbox->show_all();
}
Mainwin::~Mainwin() {}

//methods

//FILE > QUIT//
void Mainwin::on_quit_click()
{
	close();
}


//VIEW//
//view > customer
void Mainwin::on_view_customer_click()
{
	std::ostringstream oss;

	if(store->num_customers() <= 0)
	{
		oss << "<span size='14000' weight='bold'>There are currently no customers. To add a customer, click Insert > Customer.</span>";
	}
	else
	{
		oss << "<span size='20000' weight='bold'>Customers</span>\n\n<span size='14000'>";		
		//list all customers
		for(int i=0; i<store->num_customers(); ++i)
		{
			oss << i << ") " << store->customer(i) << "\n";
		}
		oss << "</span>";
	}
	set_data(oss.str());
	set_msg("");
}

//view > peripheral
void Mainwin::on_view_peripheral_click()
{
	std::ostringstream oss;
	
	//if there are currently no options
	if(store->num_options() <= 0)
	{
		oss << "<span size='14000' weight='bold'>There are currently no peripherals. To add a new peripheral, click Insert > Peripheral.</span>";
	}
	else
	{
		oss << "<span size='20000' weight='bold'>Peripherals</span>\n\n<span size='14000'>";
		//list all peripherals
		for(int i=0; i<store->num_options(); ++i)
		{
			oss << i << ") " << store->option(i) << "\n";
		}
		oss << "</span>";
	}

	set_data(oss.str());
	set_msg("");
}

//view > desktop
void Mainwin::on_view_desktop_click()
{
	std::ostringstream oss;

	if(store->num_desktops() <= 0)
	{
		oss << "<span size='14000' weight='bold'>There are currently no products. To add a new product, click Insert > Desktop.</span>";
	}
	else
	{
		oss << "<span size='20000' weight='bold'>Products</span>\n\n<span size='14000'>";
		//list all desktops
		for(int i=0; i<store->num_desktops(); ++i)
		{
			oss << i << ") " << store->desktop(i) << "\n";
		}
		oss << "</span>";
	}

	set_data(oss.str());
	set_msg("");
}

//view > order
void Mainwin::on_view_order_click()
{
	std::ostringstream oss;
	
	if(store->num_orders() <= 0)
	{
		oss << "<span size='14000' weight='bold'>There are currently no orders. To add a new order, click Insert > Order.</span>";
	}
	else
	{
		oss << "<span size='20000' weight='bold'>Order(s)</span>\n\n<span size='14000'>";
		//list out all orders
		for(int i=0; i<store->num_orders(); ++i)
		{
			oss << i << ") " << store->order(i) << '\n';
		}
		oss << "</span>";
	}

	set_data(oss.str());
	set_msg("");
}


//INSERT//
//insert > customer
void Mainwin::on_insert_customer_click()
{
	//call get_string to open up an entry dialog that asks for customer's name
	std::string name = get_string("Customer name?");
	
	if(name.size())
	{
		//get phone and email
		std::string phone = get_string("Customer phone (xxx-xxx-xxxx)? ");
		std::string email = get_string("Customer email (xxx@domain.com)?");
		//instance and add the customer to Store::add_customer
		Customer customer{name, phone, email};		
		store->add_customer(customer);

		//call on_view_customer_click to show the new customer that is added to the data area and update status bar
		on_view_customer_click();
		set_msg("Added customer " + name);
	}
}

//insert > peripheral
void Mainwin::on_insert_peripheral_click()
{
	//prompts	
	std::string s = get_string("Name of the new peripheral?");
	double cost = get_double("Cost?");
	try{
		//add new peripheral to the list that's in store		
		Options option{s, cost};
		store->add_option(option);
		on_view_peripheral_click();
		set_msg("Added peripheral " + std::to_string((store->num_options())-1));
	}catch(std::exception& e){
		std::cerr << "Invalid peripheral: " << e.what() << std::endl;
	}
}

//insert > desktop
void Mainwin::on_insert_desktop_click()
{
	//let's create a new product
	int desktop = store->new_desktop();
	on_view_desktop_click();
	set_msg("Added desktop " + std::to_string(desktop));
	
	//for the prompt	
	std::ostringstream oss;
	for(int i=0; i<store->num_options(); ++i)
	{
		oss << i << ") " << store->option(i) << '\n';
	}
	oss << "\nAdd which peripheral?";

	int option;	
	do{
		option = get_int(oss.str());

		if(option >= 0 && option < store->num_options())
		{
			store->add_option(option,desktop);
			on_view_desktop_click();
			set_msg("Added peripheral " + std::to_string(option) + " to desktop " + std::to_string(desktop));
		}
		else if(option != -1)
		{
			std::cerr << "Invalid option" << std::endl;
		}
	}while(option != -1);
}

//insert > order
void Mainwin::on_insert_order_click()
{
	int customer = -1;
	int order = -1;
	int desktop = -1;

	if(store->num_desktops() <= 0 || store->num_customers() <= 0)
	{
		set_data("<span size='14000' weight='bold'>There are currently either no customers or no products to create an order.\n\nTo add a new customer, click Insert > Customer.\nTo add a new product, click Insert > Desktop.</span>");
		return;
	}
	
	//for prompt
	std::ostringstream oss;

	for(int i=0; i<store->num_customers(); ++i)
	{
		oss << i << ") " << store->customer(i) << '\n';
	}
	oss << "\nCustomer? ";
	customer = get_int(oss.str());
	
	if(customer >= 0 && customer < store->num_customers())
	{
		try{
			order = store->new_order(customer);
			desktop = 0;
		}catch(std::exception& e){
			std::cerr << "Unable to create order for customer " << customer << std::endl;
		}

		on_view_order_click();
		set_msg("Added order " + std::to_string(order));

		//for next prompt
		oss.str("");	
		oss.clear();
		for(int i=0; i<store->num_desktops(); ++i)
		{
			oss << i << ") " << store->desktop(i) << "\n";
		}
		oss << "\nAdd which desktop to the order?";

		do{
			desktop = get_int(oss.str());
			
			if(desktop >= 0 && desktop < store->num_desktops())
			{
				try{
					store->add_desktop(desktop, order);
				}catch(std::exception& e){
					std::cerr << "Unable to add desktop " << desktop << " to order " << order << std::endl;
				}

				on_view_order_click();
				set_msg("Added desktop " + std::to_string(desktop) + " to order " + std::to_string(order));
			}
			else if(desktop != -1)
			{
				std::cerr << "Invalid desktop" << std::endl;
			}
		}while(desktop != -1);
	}
}


//ABOUT//
//about > help
void Mainwin::on_about_click()
{
	Gtk::AboutDialog dialog;

	dialog.set_transient_for(*this); //avoid the discouraging warning;
	dialog.set_program_name("Exceptional Laptops and Supercomputers Always (ELSA)");
	dialog.set_version("Version 1.0");
	dialog.set_copyright("Copyright 2019-2020");
	dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
	std::vector<Glib::ustring> authors = {"Hoang Ho"};
	dialog.set_authors(authors);
	dialog.set_comments("A management system for the ELSA store which manages customer, peripheral, product, and order information.");
	dialog.run();
}


//UTILITY METHODS//
//getters
std::string Mainwin::get_string(std::string prompt)
{
	EntryDialog ed{*this, prompt};
	ed.run();

	return ed.get_text();
}
double Mainwin::get_double(std::string prompt)
{
	double num;

	try{
		num = std::stod(get_string(prompt));
		return num;
	}catch(std::exception& e){
		return -1.0;
	}
}
int Mainwin::get_int(std::string prompt)
{
	int num;	
	try{
		num = std::stoi(get_string(prompt));
		return num;
	}catch(std::exception& e){
		return -1;
	}
}

//setters
void Mainwin::set_data(std::string s)
{
	data->set_markup(s);
}
void Mainwin::set_msg(std::string s)
{
	msg->set_markup(s);
}