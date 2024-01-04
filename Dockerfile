FROM dorowu/ubuntu-desktop-lxde-vnc

RUN wget -q -O - https://dl.google.com/linux/linux_signing_key.pub | apt-key add -

RUN apt-get update
RUN apt-get install -y \
    cmake \
    g++ \
    gdb \
    build-essential \
    && apt-get clean

WORKDIR /app

COPY . . 

EXPOSE 8080
ENV DISPLAY=:0

RUN chmod +x startup.sh

CMD ["startup.sh"]
