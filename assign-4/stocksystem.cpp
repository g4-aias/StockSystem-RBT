#include "stocksystem.h"

StockSystem::StockSystem()
{
	balance = 100000.00;
}

double StockSystem::GetBalance()
{
	return balance;
}

bool StockSystem::StockNewItem(StockItem item) // mystore.StockNewItem(StockItem(asku, adesc, aprice))
{
	// Need to check if item already exists

	if (records.Search(item) == false)
		records.Insert(item);
	else
		return false;

	return true;
}

bool StockSystem::EditStockItemDescription(unsigned int itemsku, string desc)
{
	// records.Retrieve will give the address of the 'data'
	// StockItem(itemsku, "", 0) is considered to be the 'item'
	// ptr will only point to 'item'
	StockItem* ptr = records.Retrieve(StockItem(itemsku, "", 0));

	if (ptr == NULL) 
		return false;

	ptr->SetDescription(desc);
	
	return true;
}


bool StockSystem::EditStockItemPrice(unsigned int itemsku, double retailprice)
{
	StockItem* ptr = records.Retrieve(StockItem(itemsku, "", 0));

	if (ptr == NULL)
		return false;

	ptr->SetPrice(retailprice);

	return true;
}

bool StockSystem::Restock(unsigned int itemsku, unsigned int quantity, double unitprice)
{
	StockItem* ptr = records.Retrieve(StockItem(itemsku, "", 0));

	if (ptr == NULL)
		return false;
	
	if (this->GetBalance() > quantity*unitprice)
	{
		if (ptr->GetStock() + quantity > 1000)
		{
			quantity = 1000 - ptr->GetStock();
			ptr->SetStock(1000);
		}
		else
			ptr->SetStock(ptr->GetStock()+quantity);
		
		balance = balance - quantity*unitprice;
		return true;
		
	}
	else
	{
		return false;
	}
}

bool StockSystem::Sell(unsigned int itemsku, unsigned int quantity)
{
	StockItem* ptr = records.Retrieve(StockItem(itemsku,"",0));

	if (ptr == NULL)
		return false;

	if (ptr->GetStock() == 0) // there is no stock
		return false;
	else if (ptr->GetStock() < quantity) // partial stock
	{
		balance = balance + ptr->GetStock()*ptr->GetPrice();
		ptr->SetStock(0);
		return true;
	}
	else
	{
		balance = balance + quantity*ptr->GetPrice();
		ptr->SetStock(ptr->GetStock()-quantity);
		return true;
	}
	
}