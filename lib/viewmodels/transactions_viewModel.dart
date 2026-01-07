import 'dart:io';

import 'package:flutter/material.dart';
import 'package:pf_project/models/transaction_model.dart';

class TransactionsViewModel extends ChangeNotifier {
  List<TransactionModel> transactions = [];

  String userID = "";

  Future<void> initialize() async {
    transactions.clear();
    userID = "";

    await currentUserID();

    if (userID.isEmpty) {
      debugPrint("User ID not resolved. Aborting transaction load.");
      notifyListeners();
      return;
    }

    await loadAllTransactions();
  }

  Future<void> refreshTransactions() async {
    if (userID.isEmpty) return;
    transactions.clear();
    await displayAddBalanceHistory();
    await displayExchangeHistory();
    await displayTransferHistory();
    await displayBillHistory();

    sortTransactionsByTime();
    notifyListeners();
  }

  void reset() {
    userID = "";
    transactions.clear();
    notifyListeners();
  }

  Future<void> loadAllTransactions() async {
    await displayAddBalanceHistory();
    await displayExchangeHistory();
    await displayTransferHistory();
    await displayBillHistory();
    sortTransactionsByTime();
    notifyListeners();
  }

  void sortTransactionsByTime() {
    transactions.sort((a, b) {
      final dateA = DateTime.tryParse(a.time) ?? DateTime(1970);
      final dateB = DateTime.tryParse(b.time) ?? DateTime(1970);
      return dateB.compareTo(dateA);
    });
  }

  List<TransactionModel> get latestThree =>
      transactions.length <= 3 ? transactions : transactions.sublist(0, 3);

  Future<void> currentUserID() async {
    try {
      final result = await Process.run(
        "get_uid.exe",
        [],
        workingDirectory: Directory.current.path,
      );

      int uid = result.exitCode;
      debugPrint("user id in vM: $uid");
      switch (uid) {
        case -1:
          {
            debugPrint("file opening error!");
          }
          break;
        case -2:
          {
            debugPrint("Empty session file");
          }
          break;
        case -3:
          {
            debugPrint("invalid format or currupted file");
          }
          break;
        default:
          {
            userID = uid.toString();
          }
      }
    } catch (e) {
      debugPrint("error in current user!");
    }
  }

  Future<void> displayAddBalanceHistory() async {
    try {
      final result = await Process.run("displayAddBalanceHistory.exe", [
        userID.trim(),
      ], workingDirectory: Directory.current.path);

      final output = result.stdout.toString().trim();
      if (output.isEmpty) return;

      final lines = output.split('\n');

      for (final line in lines) {
        final parts = line.split('|');
        if (parts.length < 6) continue;

        transactions.add(
          TransactionModel(
            type: TransactionType.addBalance,
            title: "Added Money",
            amount: parts[2],
            time: parts[5],
            color: Colors.green,
            details: {
              "currency": parts[1],
              "method": parts[3],
              "transactionId": parts[4],
            },
          ),
        );
      }
    } catch (e) {
      debugPrint("Error displaying add balance history: $e");
    }
  }

  Future<void> displayExchangeHistory() async {
    try {
      final result = await Process.run("displayExchangeHistory.exe", [
        userID.trim(),
      ], workingDirectory: Directory.current.path);

      final output = result.stdout.toString().trim();
      if (output.isEmpty) return;

      final lines = output.split('\n');

      for (final line in lines) {
        final parts = line.split('|');
        if (parts.length < 4) continue;

        transactions.add(
          TransactionModel(
            type: TransactionType.exchange,
            title: "Exchanged Money",
            amount: parts[2],
            time: parts[3],
            color: Colors.blue,
            details: {"currency": parts[1]},
          ),
        );
      }
    } catch (e) {
      debugPrint("Error displaying exchange history: $e");
    }
  }

  Future<void> displayTransferHistory() async {
    try {
      final result = await Process.run("displayTransferHistory.exe", [
        userID.trim(),
      ], workingDirectory: Directory.current.path);

      final output = result.stdout.toString().trim();
      if (output.isEmpty) return;

      final lines = output.split('\n');
      for (final line in lines) {
        final parts = line.split('|');
        if (parts.length < 7) continue;

        transactions.add(
          TransactionModel(
            type: TransactionType.transfer,
            title: "Transferred Money",
            amount: parts[5],
            time: parts[6],
            color: Colors.red,
            details: {
              "currency": parts[1],
              "method": parts[2],
              "account": parts[3],
              "name": parts[4],
            },
          ),
        );
      }
    } catch (e) {
      debugPrint("Error displaying transfer money history: $e");
    }
  }

  Future<void> displayBillHistory() async {
    try {
      final result = await Process.run("displayBillHistory.exe", [
        userID.trim(),
      ], workingDirectory: Directory.current.path);

      final output = result.stdout.toString().trim();
      if (output.isEmpty) return;

      final lines = output.split('\n');

      for (final line in lines) {
        final parts = line.split('|');
        if (parts.length < 7) continue;

        transactions.add(
          TransactionModel(
            type: TransactionType.bill,
            title: "Bill Payment",
            amount: parts[5],
            time: parts[6],
            color: const Color(0xFF546E7A),
            details: {
              "currency": "PKR",
              "billType": parts[1],
              "provider": parts[2],
              "name": parts[3],
              "consumerNo": parts[4],
            },
          ),
        );
      }
    } catch (e) {
      debugPrint("Error displaying bill payments history: $e");
    }
  }
}
