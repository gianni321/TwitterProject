import tweepy
import sys
import datetime
import json
import urllib
from urllib.request import urlopen


'''
GRV post_tweet.py.
How TO Run: $python post_tweet.py 
This program needs a file named grids.txt to run
This is the format this program can parse 

$GPGLL,4036.05215,N,10504.19257,W,220029.00,A,A*7A

Pass in a file that has the contents of what should be tweeted out.
The current date will be appended to the begining of the tweet.
@WARNING This code will not be able to post the same status twice. @Fix by adding in date.
'''


def parse_weather(grid):
    report = "No weather"

    # Move decimal place over and add negative sign if needed
    index = grid[1].find('.')
    grid1 = grid[1][0:index-2] + "." + \
        grid[1][index-2:index] + grid[1][index+1:]
    if(grid[2] == 'S'):
        grid1 = "-" + grid1

    # Move decimal place over and add negative sign if needed
    index = grid[3].find('.')
    grid2 = grid[3][0:index-2] + "." + \
        grid[3][index-2:index] + grid[3][index+1:]
    if(grid[4] == 'W'):
        grid2 = "-" + grid2

    # Combine into one grid string and call api
    grid = grid1 + ',' + grid2
    with urlopen(f"https://api.weather.gov/points/{grid}/forecast") as response:
        text = response.read()
        text = json.loads(text)

        # Get icon and detailed forecast
        url = text["properties"]["periods"][0]["icon"]
        report = text["properties"]["periods"][0]["detailedForecast"]

        # Write weather forecast
        with urlopen(url) as response:
            image = response.read()
            with open('weather_image.png', 'wb') as f:
                f.write(image)

        # # Write weather image
        # with open("weather_data.txt", 'w') as f:
        #     f.write(report)
    return report


def post_tweet(tweet):
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
    # Verify auth
    api = tweepy.API(auth)

    # Seting "@var tweet" to be posted as status.

    # Getting picture
    media = api.media_upload("weather_image.png")

    # Sending
    status = api.update_status(status=tweet, media_ids=[media.media_id])


if __name__ == "__main__":
    # Open grid file
    with open("grids.txt", 'r') as f:
        grid = f.readline().split(',')

    # Pull out a parsed message
    contents = parse_weather(grid)

    # Get date
    now = datetime.datetime.now()
    # Format date
    now = now.strftime("%Y-%m-%d %H:%M")
    # Show what will be printed (May need to be removed)
    print("This is the content that will be tweeted out: " +
          str(now) + "\n" + contents)
    # Load into our post tweet with date
    tweet = str(now) + "\n" + contents
    post_tweet(tweet)
