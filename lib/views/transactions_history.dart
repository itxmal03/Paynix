import 'package:flutter/material.dart';
import 'package:pf_project/models/transaction_model.dart';
import 'package:pf_project/viewmodels/transactions_viewmodel.dart';
import 'package:provider/provider.dart';

class TransactionsHistory extends StatefulWidget {
  const TransactionsHistory({super.key});

  @override
  State<TransactionsHistory> createState() => _TransactionsHistoryState();
}

class _TransactionsHistoryState extends State<TransactionsHistory> {
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: PreferredSize(
        preferredSize: const Size.fromHeight(65),
        child: AppBar(
          leadingWidth: 40,
          leading: Padding(
            padding: const EdgeInsets.only(top: 8.0),
            child: IconButton(
              icon: const Icon(Icons.arrow_back),
              onPressed: () => Navigator.pop(context),
            ),
          ),
          flexibleSpace: Container(
            decoration: const BoxDecoration(
              gradient: LinearGradient(
                colors: [Color(0xff136a8a), Color(0xff57C785)],
                begin: Alignment.topLeft,
                end: Alignment.bottomRight,
              ),
            ),
          ),
          title: const Padding(
            padding: EdgeInsets.only(top: 8.0),
            child: Text(
              "Transactions History",
              style: TextStyle(fontSize: 25, fontWeight: FontWeight.w600),
            ),
          ),
        ),
      ),
      body: Consumer<TransactionsViewModel>(
        builder: (ctx, val, child) => val.transactions.isEmpty
            ? const Center(
                child: Text(
                  "No Transaction yet!",
                  style: TextStyle(fontWeight: FontWeight.w500),
                ),
              )
            : ListView.builder(
                itemCount: val.transactions.length,
                itemBuilder: (context, index) {
                  return transactionItem(val.transactions[index]);
                },
              ),
      ),
    );
  }
}

Widget transactionItem(TransactionModel tx) {
  return Card(
    elevation: 2,
    shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(14)),
    child: ListTile(
      leading: CircleAvatar(
        backgroundColor: tx.color.withValues(alpha: 200),
        child: Icon(Icons.account_balance_wallet, color: tx.color),
      ),
      title: Text(
        tx.title,
        style: const TextStyle(fontWeight: FontWeight.w600),
      ),
      subtitle: _buildSubtitle(tx),
      trailing: Text(
        tx.amount,
        style: TextStyle(
          color: tx.color,
          fontWeight: FontWeight.bold,
          fontSize: 16,
        ),
      ),
    ),
  );
}

Widget _buildSubtitle(TransactionModel tx) {
  switch (tx.type) {
    case TransactionType.bill:
      return Text(
        "${tx.details["billType"]} • ${tx.details["provider"]}\n"
        "Consumer: ${tx.details["consumerNo"]}\n"
        "Time: ${tx.time}",
      );

    case TransactionType.transfer:
      return Text(
        "To: ${tx.details["name"]} \n"
        "Method: ${tx.details["method"]}\t Account No/UID: ${tx.details["account"]}\n"
        "Time: ${tx.time}",
      );

    case TransactionType.exchange:
      return Text("Currency: ${tx.details["currency"]}\nTime: ${tx.time}");

    case TransactionType.addBalance:
      return Text(
        "Method: ${tx.details["method"]}\n"
        "Transaction ID: ${tx.details["transactionId"]}\n"
        "Time: ${tx.time}",
      );
  }
}
