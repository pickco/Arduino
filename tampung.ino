void data() {
  if (datachar == 'A')
  {
    while (datachar != 'B')
    {
      if (isdigit(datachar))
      {
        numerik = numerik * 10 + (datachar - '0');
      }
      datachar = radio.read();
    }
    latitude = numerik;
    numerik = 0;
  }

  if (datachar == 'B')
  {
    while (datachar != 'C')
    {
      if (isdigit(datachar))
      {
        numerik = numerik * 10 + (datachar - '0');
      }
      datachar = radio.read();
    }
    longitude = numerik;
    numerik = 0;
  }
  
  if (datachar == 'C')
  {
    while (datachar != 'D')
    {
      if (isdigit(datachar))
      {
        numerik = numerik * 10 + (datachar - '0');
      }
      datachar = radio.read();
    }
    temperature = numerik;
    numerik = 0;
  }

  if (datachar == 'D')
  {
    while (datachar != ';')
    {
      if (isdigit(datachar))
      {
        numerik = numerik * 10 + (datachar - '0');
      }
      datachar = radio.read();
    }
    humidity = numerik;
    numerik = 0;
  }
}
