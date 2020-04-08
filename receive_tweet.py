# GRV Work in progress

import os
import tweepy as tw
import pandas as pd

consumer_key = 'yourkeyhere'
consumer_secret = 'yourkeyhere'
access_token = 'yourkeyhere'
access_token_secret = 'yourkeyhere'

auth = tw.OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_token_secret)
api = tw.API(auth, wait_on_rate_limit=True)


search_words = "#wildfires"
date_since = "2018-11-16"


# Collect tweets
tweets = tw.Cursor(api.search,
                   q=search_words,
                   lang="en",
                   since=date_since).items(5)
[tweet.text for tweet in tweets]
