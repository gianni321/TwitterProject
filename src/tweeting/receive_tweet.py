import tweepy
import time
import sys
import datetime
import json
import urllib

# Twitter Tokens
twitter_auth_keys = {
    "consumer_key": "8r3djrKFhQKLFn7pi53VLOAtd",
    "consumer_secret": "m8xIrhQtX6lfSagxbnOQMrNjpVWUCkhX7ccHo7TYOtdV2fBDW6",
    "access_token": "1231271703709286400-cLDovtBPZwJfoHpCptgWqMzHte6d27",
    "access_token_secret": "mTeSKmvavmBFxPX3Drvi7EqAbEpC6BNqZAgjtwHreBVTE"
}
# Loading in consumer tokens
auth = tweepy.OAuthHandler(
    twitter_auth_keys['consumer_key'],
    twitter_auth_keys['consumer_secret']
)
# Loading in access tokens
auth.set_access_token(
    twitter_auth_keys['access_token'],
    twitter_auth_keys['access_token_secret']
)
api = tweepy.API(auth)

mentions_file = "mentions.txt"

def retrieve_last_seen_id(file_name):
    f_read = open(file_name, 'r')
    last_seen_id = int(f_read.read().strip())
    f_read.close
    return last_seen_id

def store_last_seen_id(last_seen_id, file_name):
    f_write = open(file_name, 'w')
    f_write.write(str(last_seen_id))
    f_write.close()
    return

def retrieve_mentions():
    print("Im trying...")
    last_seen_id = retrieve_last_seen_id(mentions_file)
    mentions = api.mentions_timeline(last_seen_id, tweet_mode = "extended")
    for mention in reversed(mentions):
        if not mention:
            return
        print(str(mention.id) + '-' + mention.full_text, flush=True)
        print(mention.full_text[16:])
        last_mention = mention.id
        store_last_seen_id(last_mention, mentions_file)

while True:
    retrieve_mentions()
    time.sleep(10)