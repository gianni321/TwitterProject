#!/usr/bin/python3

import tweepy
import time
import sys
import datetime
import json
import urllib
import auth
import os


mentions_file = "/home/pi/TwitterProject/src/tweeting/mentions.txt"


def retrieve_last_seen_id(file_name):
    f_read = open(file_name, 'r')
    last_seen_id = int(f_read.read().strip())
    f_read.close
    return last_seen_id


def store_last_seen_id(last_seen_id, file_name):
    f_write = open(file_name, 'w')
    f_write.write(str(last_seen_id))
    f_write.close()
    # return str(last_seen_id)


def retrieve_mentions():
    print("Searching for tweets...", flush=True)
    last_seen_id = retrieve_last_seen_id(mentions_file)
    mentions = api.mentions_timeline(last_seen_id, tweet_mode="extended")
    for mention in reversed(mentions):
        # mention.text
        if not mention:
            return
        print("New tweet found, replying...", flush=True)
        # print(str(mention.id) + '-' + mention.full_text, flush=True)
        # print(mention.full_text[16:])
        last_mention = mention.id
        store_last_seen_id(last_mention, mentions_file)
        post_tweet_call(mention.full_text[16:].strip(), mention.id)


def post_tweet_call(text, id):
    print("text: ", text)
    print("id: ", id)

    os.system("python3 /home/pi/TwitterProject/src/tweeting/post_tweet.py \"{}\" \"{}\"".format(text, id))


while True:
    # # Twitter Tokens
    api = auth.getAuth()
    while True:
        retrieve_mentions()
        time.sleep(10)
