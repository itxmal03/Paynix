import 'dart:ui';

enum TransactionType { addBalance, exchange, transfer, bill }

class TransactionModel {
  final TransactionType type;
  final String title;
  final String amount;
  final String time;
  final Color color;
  final Map<String, String> details;

  TransactionModel({
    required this.type,
    required this.title,
    required this.amount,
    required this.time,
    required this.color,
    required this.details,
  });
}