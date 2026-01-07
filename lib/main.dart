import 'package:flutter/material.dart';
import 'package:pf_project/viewmodels/theme_viewmodel.dart';
import 'package:pf_project/viewmodels/transactions_viewmodel.dart';
import 'package:pf_project/views/splash_screen.dart';
import 'package:provider/provider.dart';

void main() {
  runApp(
    MultiProvider(
      providers: [
        ChangeNotifierProvider(create: (context) => ThemeViewmodel()),
        ChangeNotifierProvider(create: (context)=>TransactionsViewModel())
      ],
      child: const MainApp(),
    ),
  );
}

class MainApp extends StatelessWidget {
  const MainApp({super.key});
  @override
  Widget build(BuildContext context) {
    final theme = Provider.of<ThemeViewmodel>(context);
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      themeMode: theme.isDark ? ThemeMode.dark : ThemeMode.light,
      darkTheme: ThemeData.dark(),
      home: SplashScreen(),
    );
  }
}
