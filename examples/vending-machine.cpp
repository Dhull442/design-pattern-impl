/*
Design discussion:
Requirements:
client side:
- getItem(s)
- deleteItem from List
- makePayment


- restockItems
- getEarnings
- getStockInfo


Item{
	id, name, price, stockLeft;
}
VendingMacine{
	- Items
	- earnings
	- ActiveItems
	- ActiveTotal
	
	ListItems getAllItems(){}
	<Items, total> addItems(){}
	<items, total> removeItems(){}
	<Items, change> makePayment(Items){}


	restockItems(list items)
	deleteItems(list items)
	money getEarning()

}
*/