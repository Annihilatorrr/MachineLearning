FROM gcc:latest

COPY ./ /usr/src/Ml/
COPY ./Ml.lib /usr/src/Ml/Ml.lib

WORKDIR /usr/src/Ml

RUN ls

WORKDIR ./Ml.lib

RUN pwd

RUN ls

RUN make

WORKDIR ../Ml.app

RUN pwd
RUN ls
RUN make
RUN ls

ENV LD_LIBRARY_PATH=/usr/src/Ml/Ml.lib:$LD_LIBRARY_PATH
CMD ["./mltest"]

  
