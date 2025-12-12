import 'package:flutter/material.dart';

class Utils {
  void flutterToast(String toast ,BuildContext context) {
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(
        backgroundColor: Color(0xff57C785),
        duration: Duration(seconds: 2),
        behavior: SnackBarBehavior.floating,
        margin: EdgeInsets.only(bottom: 50, left: 900, right: 50),
        content: Center(
          child: Text(toast, style: TextStyle(color: Colors.black)),
        ),
      ),
    );
  }
}
