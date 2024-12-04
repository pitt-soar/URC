FROM dustynv/ros:humble-ros-base-l4t-r32.7.1

WORKDIR /app

# TODO : properly do this
# COPY *.py /app/

RUN apt-get update && apt-get install -y python3-pip && \
    pip install supervisor &&\
    pip3 install --no-cache-dir pyserial
