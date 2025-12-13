import 'package:flutter/material.dart';

class TransactionsHistory extends StatefulWidget {
  const TransactionsHistory({super.key});

  @override
  State<TransactionsHistory> createState() => _TransactionsHistoryState();
}

class _TransactionsHistoryState extends State<TransactionsHistory> {
  List<Map<String, dynamic>> transaction = [
    {
      "action": "Added Money",
      "amount": "1200",
      "date": "13 Dec 2025",
      "color": Colors.green,
    },
    {
      "action": "Withdraw",
      "amount": "500",
      "date": "12 Dec 2025",
      "color": Colors.red,
    },
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: PreferredSize(
        preferredSize: Size.fromHeight(65),
        child: AppBar(
          leadingWidth: 40,
          leading: Padding(
            padding: const EdgeInsets.only(top: 8.0),
            child: IconButton(
              icon: Icon(Icons.arrow_back),
              onPressed: () {
                Navigator.pop(context);
              },
            ),
          ),
          flexibleSpace: Container(
            decoration: BoxDecoration(
              gradient: LinearGradient(
                colors: [Color(0xff136a8a), Color(0xff57C785)],
                begin: Alignment.topLeft,
                end: Alignment.bottomRight,
              ),
            ),
          ),
          title: Padding(
            padding: const EdgeInsets.only(top: 8.0),
            child: Text(
              "Transactions History",
              style: TextStyle(fontSize: 25, fontWeight: FontWeight.w600),
            ),
          ),
        ),
      ),
      body: Column(
        children: [
          Expanded(
            child: transaction.isEmpty
                ? Center(
                    child: Text(
                      "No Transaction yet!",
                      style: TextStyle(fontWeight: FontWeight.w500),
                    ),
                  )
                : ListView.builder(
                    itemCount: transaction.length,
                    itemBuilder: (context, index) {
                      return transactionItem(
                        transaction[index]["action"],
                        transaction[index]["amount"],
                        transaction[index]["date"],
                        transaction[index]["color"],
                      );
                    },
                  ),
          ),
        ],
      ),
    );
  }
}

Widget transactionItem(String title, String amount, String date, Color color) {
  return Card(
    elevation: 2,
    shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(14)),
    child: ListTile(
      leading: CircleAvatar(
        backgroundColor: color.withOpacity(0.2),
        child: Icon(Icons.account_balance_wallet, color: color),
      ),
      title: Text(title, style: TextStyle(fontWeight: FontWeight.w600)),
      subtitle: Text(date),
      trailing: Text(
        amount,
        style: TextStyle(
          color: color,
          fontWeight: FontWeight.bold,
          fontSize: 16,
        ),
      ),
    ),
  );
}
