// Cached snapshot from Agmarknet API - 25 Aug 2026
// Source: https://api.data.gov.in/resource/9ef84268-d588-465a-a308-a864a43d0070
// Total Maharashtra records: 1289 (25/08/2026)
// Demo fallback: serve these if API is down at venue

export type AgmarknetRecord = {
  state: string; district: string; market: string; commodity: string;
  variety: string; grade: string; arrival_date: string;
  min_price: number; max_price: number; modal_price: number;
};

// Maharashtra onion records - live snapshot 25 Aug 2026
export const cachedOnion: AgmarknetRecord[] = [
  { state:"Maharashtra", district:"Amarawati", market:"Amrawati APMC", commodity:"Onion", variety:"Local", grade:"Local", arrival_date:"25/08/2026", min_price:2000, max_price:5000, modal_price:3500 },
  { state:"Maharashtra", district:"Ahilyanagar", market:"Omchatinya Multi State Agro", commodity:"Onion", variety:"Other", grade:"Local", arrival_date:"25/08/2026", min_price:1000, max_price:5500, modal_price:3800 },
  { state:"Maharashtra", district:"Solapur", market:"SHRI.SIDDHESHWAR APMC", commodity:"Onion", variety:"Red", grade:"Local", arrival_date:"25/08/2026", min_price:500, max_price:5500, modal_price:3000 },
  { state:"Maharashtra", district:"Nashik", market:"Kalvan APMC", commodity:"Onion", variety:"Unhali", grade:"Local", arrival_date:"25/08/2026", min_price:1500, max_price:5000, modal_price:4200 },
  { state:"Maharashtra", district:"Nashik", market:"Devala APMC", commodity:"Onion", variety:"Unhali", grade:"Local", arrival_date:"25/08/2026", min_price:700, max_price:4325, modal_price:3925 },
  { state:"Maharashtra", district:"Nashik", market:"Lasalgaon APMC", commodity:"Onion", variety:"Red", grade:"FAQ", arrival_date:"25/08/2026", min_price:1800, max_price:4500, modal_price:3600 },
  { state:"Maharashtra", district:"Pune", market:"Pune APMC", commodity:"Onion", variety:"Red", grade:"FAQ", arrival_date:"25/08/2026", min_price:2200, max_price:4800, modal_price:3450 },
  { state:"Maharashtra", district:"Nagpur", market:"Nagpur APMC", commodity:"Onion", variety:"Red", grade:"FAQ", arrival_date:"25/08/2026", min_price:2000, max_price:4200, modal_price:3200 },
  { state:"Maharashtra", district:"Nashik", market:"Malegaon APMC", commodity:"Onion", variety:"Local", grade:"Local", arrival_date:"25/08/2026", min_price:1200, max_price:3800, modal_price:2800 },
  { state:"Maharashtra", district:"Jalna", market:"Jalna APMC", commodity:"Onion", variety:"Other", grade:"Local", arrival_date:"25/08/2026", min_price:1500, max_price:4000, modal_price:3100 },
];

// Other key commodities for Maharashtra (live 25 Aug)
export const cachedOtherCommodities: AgmarknetRecord[] = [
  { state:"Maharashtra", district:"Parbhani", market:"Shree Salasar Krushi Bazar", commodity:"Soyabean", variety:"Other", grade:"Local", arrival_date:"25/08/2026", min_price:3000, max_price:5600, modal_price:5500 },
  { state:"Maharashtra", district:"Parbhani", market:"Shree Salasar Krushi Bazar", commodity:"Bengal Gram", variety:"Other", grade:"Local", arrival_date:"25/08/2026", min_price:5500, max_price:5800, modal_price:5800 },
  { state:"Maharashtra", district:"Nashik", market:"Malegaon APMC", commodity:"Bajra", variety:"Other", grade:"Non-FAQ", arrival_date:"25/08/2026", min_price:2081, max_price:2701, modal_price:2500 },
  { state:"Maharashtra", district:"Nashik", market:"Malegaon APMC", commodity:"Groundnut", variety:"Other", grade:"Non-FAQ", arrival_date:"25/08/2026", min_price:5900, max_price:7262, modal_price:7260 },
  { state:"Maharashtra", district:"Nagpur", market:"Nagpur APMC", commodity:"Wheat", variety:"Other", grade:"Non-FAQ", arrival_date:"25/08/2026", min_price:2510, max_price:2584, modal_price:2565 },
  { state:"Maharashtra", district:"Nagpur", market:"Nagpur APMC", commodity:"Tur Dal", variety:"Other", grade:"FAQ", arrival_date:"25/08/2026", min_price:8000, max_price:8200, modal_price:8150 },
  { state:"Maharashtra", district:"Nagpur", market:"Nagpur APMC", commodity:"Tur Dal", variety:"Other", grade:"Non-FAQ", arrival_date:"25/08/2026", min_price:7600, max_price:7999, modal_price:7899 },
  { state:"Maharashtra", district:"Nagpur", market:"Nagpur APMC", commodity:"Pomegranate", variety:"Other", grade:"Local", arrival_date:"25/08/2026", min_price:2000, max_price:6000, modal_price:5000 },
];

export const API_KEY = "579b464db66ec23bdd000001cdd3946e44ce4aad7209ff7b23ac571b";
export const RESOURCE_ID = "9ef84268-d588-465a-a308-a864a43d0070";
export const API_BASE = `https://api.data.gov.in/resource/${RESOURCE_ID}`;
