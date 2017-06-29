void drawSplash() { 
  
  gameState = STATE_GAME_NO_SELECTION;
  
}

void drawGameOver() { 
  
  arduboy.clear();
  arduboy.setCursor(12, 30);
  arduboy.print("Congratulations");
  arduboy.display();
  delay(2000);

  puzzleIdx++;
  
}
