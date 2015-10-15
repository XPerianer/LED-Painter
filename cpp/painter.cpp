//  LED-Painter, to draw live on a LED-Matrix
//  Copyright (C) 2015 Dominik Meier(XPerianer)
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//  E-Mail: Hiscore.pressthebutton@hotmail.de

#include "painter.h"

Canvas *canvas;
GPIO io;

struct ColorStruct{
  int r,g,b;
};
ColorStruct matrix[32][32];


//Needed for Socket
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int socketfunction(){
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rv = getaddrinfo("192.168.178.45", PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    while(true){ //Loop through the whole connecting thing in case the server fucks up

    do {
    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }

        break;
      }
      usleep(1000000 * 2);
    } while(p == NULL);

    /*if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");

        return 2;
    }*/

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("client: connecting to %s\n", s);

    //freeaddrinfo(servinfo); // all done with this structure //We need it later if we want to connect multiple times

    while(true){ //Get new Positional data the whole time
    std::string answer;
    try{ //Be safe if communication fails
    if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
        perror("recv");
      //  exit(1);
    }

    buf[numbytes] = '\0';

    for(int i=0;i< numbytes;i++){
      answer += buf[i];
    }
    //std::cout << answer << std::endl;
    //Set everything
    int x = std::stoi(answer.erase(0,1));
    answer = answer.substr(answer.find_first_of(",") +1);
    int y = std::stoi(answer);
    answer = answer.substr(answer.find_first_of(",")+1);
    bool light =  (bool) std::stoi(answer);
    answer = answer.substr(answer.find_first_of(",")+1);
    int r = std::stoi(answer);
    answer = answer.substr(answer.find_first_of(",")+1);
    int g = std::stoi(answer);
    answer = answer.substr(answer.find_first_of(",")+1);
    int b = std::stoi(answer);

    //std::cout << x << " " << y << " " << light << " " << r << " " << g << " " << b << std::endl;

    if(light==1){
    canvas->SetPixel(x,y,r,g,b);
    matrix[x][y].r = r;
    matrix[x][y].g = g;
    matrix[x][y].b = b;
    usleep(1000 * 10);
    }
    else{
      canvas->SetPixel(x,y,0,0,0);
      matrix[x][y].r = 0;
      matrix[x][y].g = 0;
      matrix[x][y].b = 0;

      usleep(1000 * 10);
    }
    }
    catch (...){
      std::cout << "Error at Socket reading" << std::endl;
      usleep(1000000*1);
      break;
    }

  }
    //printf("client: received '%s'\n",buf);
    close(sockfd);

  }

    return 0;
}


int main(int argc, char *argv[]) {
  std::cout << "Initalisation begins" << std::endl;
  if (!io.Init()){
    std::cout << "Initalisieren fehlgeschlagen" << std::endl;
    }
  for(int i=0;i<32;i++){
    for(int j=0;j<32;j++){
      matrix[i][j].r = 0;
      matrix[i][j].g = 0;
      matrix[i][j].b = 0;
    }
  }
  /*
   * Set up the RGBMatrix. It implements a 'Canvas' interface.
   */
   int rows = 32;    // A 32x32 display. Use 16 when this is a 16x32 display.
   int chain = 1;    // Number of boards chained together.
   int parallel = 1; // Number of chains in parallel (1..3). > 1 for plus or Pi2
   canvas = new RGBMatrix(&io, rows, chain, parallel);
   std::cout << "Initalisation finished" << std::endl;

  std::thread socket_thread(socketfunction);
  std::cout << "Press Enter to abort" << std::endl;
  getchar();

  canvas->Clear();
  std::ofstream file;
  file.open("test.rgb");
  for(int i=0;i<32;i++){
    for(int j=0;j<32;j++){
       file << matrix[i][j].r << " " << matrix[i][j].g << " " << matrix[i][j].b << std::endl;
    }
  }
  file.close();
  return 0;
}
