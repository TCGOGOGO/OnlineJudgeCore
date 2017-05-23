FROM ubuntu:latest
RUN rm /etc/apt/sources.list
COPY sources.list /etc/apt/
RUN apt-get update
RUN apt-get -y install build-essential software-properties-common python-software-properties python python3 git
RUN add-apt-repository -y ppa:webupd8team/java
RUN echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections
RUN echo debconf shared/accepted-oracle-license-v1-1 seen true | debconf-set-selections
RUN apt-get update
RUN apt-get install -y oracle-java8-installer

RUN apt-get -y install scons
COPY jsoncpp-src-0.5.0.tar.gz /tmp
RUN cd /tmp && tar -xvzf jsoncpp-src-0.5.0.tar.gz && cd jsoncpp-src-0.5.0 && scons platform=linux-gcc
RUN mv /tmp/jsoncpp-src-0.5.0/libs/linux-gcc-5.4.0/libjson_linux-gcc-5.4.0_libmt.a /tmp/jsoncpp-src-0.5.0/libs/linux-gcc-5.4.0/libjson.a && cp -rf /tmp/jsoncpp-src-0.5.0/include/json /usr/include/ && cp /tmp/jsoncpp-src-0.5.0/libs/linux-gcc-5.4.0/libjson.a /usr/local/lib/

#RUN cd /tmp && git clone https://github.com/TCGOGOGO/OnlineJudgeCore.git && cd OnlineJudgeCore && make

RUN cd /tmp && cd OnlineJudgeCore && make
RUN cd /tmp/OnlineJudgeCore && chmod 777 judge

WORKDIR /tmp/OnlineJudgeCore/test/
EXPOSE 8080
CMD cd /tmp/OnlineJudgeCore && ./judge -c test/a.cpp -l 2 -d test && cat /tmp/OnlineJudgeCore/test/result.json